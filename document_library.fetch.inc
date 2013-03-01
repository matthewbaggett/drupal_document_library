<?php 
function document_library_file_fetch($fid){
	$fid = intval($fid);
	$doc = document::search()->where('fid', $fid)->execOne();
	header("Content-Type: {$doc->mimetype}");
	echo $doc->data;
	exit;
}