<?php 
require_once(DRUPAL_ROOT . "/" . drupal_get_path('module', 'active_record') . "/lib/versioned_active_record.php");

class document extends versioned_active_record{
	protected $_table = "document_library_files";
	protected $_cfg_deleteable	= true;
	
	protected $_user;

	/**
	 * Get the User that wrote this answer originally
	 * @return user_active_record
	 */
	public function get_user(){
		if(!$this->_user){
			$this->_user = user_active_record::search()->where('uid', $this->uid)->execOne();
		}
		return $this->_user;
	}
	
	public function get_file_path(){
		return "document_library/fetch/{$this->fid}/{$this->filename}";
	}

	public function filename_slug(){
		return $this->_slugify($this->filename);
	}
	
	public function get_slug(){
		return "{$this->fid}-{$this->filename_slug()}";
	}

  /**
   * Is this Document sticky?
   *
   * @return bool
   */
  public function is_sticky(){
    return $this->sticky=="Yes" ? true : false;
  }

  /**
   * Set this Document to sticky. Has Implicit save.
   * @return document
   */
  public function set_sticky(){
    $this->sticky = "Yes";
    $this->save();
    return $this;
  }

  /**
   * Set this Document to not sticky. Has Implicit save.
   * @return document
   */
  public function set_not_sticky(){
    $this->sticky = "No";
    $this->save();
    return $this;
  }
}