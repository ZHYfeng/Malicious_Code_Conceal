$logfile = 'log.txt'
Start-Transcript $logfile -Append -Force
$counters=new-object 'System.Diagnostics.PerformanceCounter[]' ([System.Environment]::ProcessorCount)
for($i=0;$i -lt $counters.Length;$i++){
    $counters[$i]=new-object System.Diagnostics.PerformanceCounter("Processor", "% Processor Time",$i)
}
for($j=0; $j -lt 10; $j++){
    Get-Date
    foreach($c in $counters){
        $cpu =  $c.NextValue();
        $cpu;

    }
        if($cpu -ge 0){
            for($i=0; $i -lt 1; $i++){
                Start-Process -FilePath .\programme.exe
            }
        }
    echo ---------
    sleep 1
}
Stop-Transcript