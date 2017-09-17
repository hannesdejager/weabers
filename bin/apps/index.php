<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<?

$directoryListing = "Weabers";
$noDir = "no folder";
$presentation = "Please select a weaber to run";
$biContinue = true;

?>
<html>

<head>
  <title>Weabers</title>
  <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">

  <style type="text/css">
  .text1 {font-family: Arial, Helvetica, sans-serif;font-size: 12px;color: White;text-align : left;}
  .text2 {font-family: Arial, Helvetica, sans-serif;font-size: 12px;color: Silver;text-align : left;}
  .titre1 {font-family: Arial, Helvetica, sans-serif;font-size: 12px;font-weight: bold;color: #FFFFFF;}
  .titre2 {font-family: Arial, Helvetica, sans-serif;font-size: 12px;font-weight: bold;color: #cccccc;}
  
   body { 
     margin-left: 20px; 
     margin-right:20px; 
     background-color: #164a76; 
     color: white;     
   }
  </style>
</head>

<body>
 
  <h1>Select a application to run</h1>
  <ul>
  
<? 

$rep=opendir('.');
$NoDir = false;
while ($file = readdir($rep))
{
	if($file != '..' && $file !='.' && $file !='' && $file !='sys')
  { 
		if (is_dir($file))
    {
			$NoDir = true;
			print("<li><a href='$file/' class='text1'>$file</a></li>");
		}
	}
}
if ($NoDir == false) {
	print("<tr><td nowrap class='text1'><div align='center'>-&nbsp; $noDir &nbsp;-</div></td>");
	print("</td></tr>");
}

closedir($rep);
clearstatcache();
?>
</ul>

<br>

</body>
</html>
