package gov.nysenate.services.model;

public class Social {
	String twitter;
	String youtube;
	String myspace;
	String picasa;
	String flickr;
	String facebook;
	
	public Social() {
		
	}
	
	public Social(String twitter, String youtube, String myspace,
			String picasa, String flickr, String facebook) {
		this.twitter = twitter;
		this.youtube = youtube;
		this.myspace = myspace;
		this.picasa = picasa;
		this.flickr = flickr;
		this.facebook = facebook;
	}

	public String getTwitter() {
		return twitter;
	}

	public String getYoutube() {
		return youtube;
	}

	public String getMyspace() {
		return myspace;
	}

	public String getPicasa() {
		return picasa;
	}

	public String getFlickr() {
		return flickr;
	}

	public String getFacebook() {
		return facebook;
	}

	public void setTwitter(String twitter) {
		this.twitter = twitter;
	}

	public void setYoutube(String youtube) {
		this.youtube = youtube;
	}

	public void setMyspace(String myspace) {
		this.myspace = myspace;
	}

	public void setPicasa(String picasa) {
		this.picasa = picasa;
	}

	public void setFlickr(String flickr) {
		this.flickr = flickr;
	}

	public void setFacebook(String facebook) {
		this.facebook = facebook;
	}
}