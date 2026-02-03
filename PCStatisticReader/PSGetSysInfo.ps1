<#  
*Created By - Logan Bernthall - 01/02/2026
*Part of my M5StckProject, Powershell script used to collect sys metrics
#> 

function GetCPUParams
{

#Get CPU Load
$TotalLoads = (wmic cpu get LoadPercentage |
    Select-Object -Skip 1 |
    Where-Object { $_ -match '\d+' } |
    ForEach-Object { [int]$_ }
)

$TotalTemp = Get-CimInstance -Namespace root/wmi -ClassName MsAcpi_ThermalZoneTemperature |
    Select-Object -First 1 -ExpandProperty CurrentTemperature |
    ForEach-Object { "{0} C" -f [math]::Round(($_ - 2732) / 10) }

    return @{
        CPU  = $TotalLoads
        Temp = $TotalTemp
    }

}

function GetRAMParams
{

#Get Ram usage
$TotalUsage = (Get-CimInstance -ClassName CIM_OperatingSystem).FreePhysicalMemory / 1024

return [math]::Round($TotalUsage)

}

Function FormatToJSON
{
#Converts to JSON format
    
    $cpu = GetCPUParams
    $ram = GetRAMParams

    [PSCustomObject]@{
        Temp     = $cpu.Temp
        RamFree  = $ram
        CPU      = $cpu.CPU
    }

}

#Loop every 5 seconds
while ($true) {FormatToJSON | ConvertTo-Json -Compress; Start-Sleep -Seconds 5}