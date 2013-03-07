<?php 
function document_library_file_fetch($fid){
	$fid = intval($fid);
	$doc = document::search()->where('fid', $fid)->execOne();
	//header("Content-Type: {$doc->mimetype}");
	header("Content-Type: application/force-download");
	header("Content-Type: application/octet-stream");
	header("Content-Type: application/download");
	echo $doc->data;
	exit;
}