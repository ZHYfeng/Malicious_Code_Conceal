while ($true)
{
    $cores = (Get-WmiObject -Query "select Name, PercentProcessorTime from Win32_PerfFormattedData_PerfOS_Processor")
    # $cores | foreach-object { write-host "$($_.Name): $($_.PercentProcessorTime)" }; 
    $cores | foreach-object { write-host "$($_.PercentProcessorTime) " }; 
    echo \n
    Start-Sleep -m 200
}