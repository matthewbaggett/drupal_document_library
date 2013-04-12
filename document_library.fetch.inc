<?php 
function document_library_file_fetch($fid){
	$fid = intval($fid);
	$doc = document::search()->where('fid', $fid)->execOne();
	header("Content-Type: {$doc->mimetype}");
	header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
	header("Cache-Control: private", false); // required for certain browsers
	header("Content-Disposition: attachment; filename=\"{$doc->filename}\"");

	echo base64_decode($doc->data);
	exit;
}