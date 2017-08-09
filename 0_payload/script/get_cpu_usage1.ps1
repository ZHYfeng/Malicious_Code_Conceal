$counters=new-object 'System.Diagnostics.PerformanceCounter[]' ([System.Environment]::ProcessorCount)
for($i=0;$i -lt $counters.Length;$i++){
    $counters[$i]=new-object System.Diagnostics.PerformanceCounter("Processor", "% Processor Time",$i)
}
while(1){
    Get-Date
    foreach($c in $counters){
        $c.NextValue();
    }
    echo ---------
    sleep 1
}