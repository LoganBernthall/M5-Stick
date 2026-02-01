<#  
*Created By - Logan Bernthall - 01/02/2026
*Part of my M5StckProject, Powershell script used to collect sys metrics
#> 

function GetCPUParams
{

#Get CPU Load
$TotalLoads = (wmic cpu get LoadPercentage)

#Get CPU Temp
$TotalTemp = (Get-CimInstance -Namespace root/wmi -ClassName MsAcpi_ThermalZoneTemperature -Filter "Active='True' and CurrentTemperature<>2732" -Property InstanceName, CurrentTemperature |
    Select-Object InstanceName, @{n='CurrentTemperatureC';e={'{0:n0} C' -f (($_.CurrentTemperature - 2732) / 10.0)}})

Write-Output $TotalLoads $TotalTemp
}

function GetRAMParams
{

#Get Ram usage
$TotalUsage = (Get-CimInstance -ClassName CIM_OperatingSystem).FreePhysicalMemory / 1024
Write-Output "Memory Free (MB)" $TotalUsage

}

#Loop every 5 seconds
while ($true) {GetCPUParams; GetRamParams; Start-Sleep -Seconds 5}