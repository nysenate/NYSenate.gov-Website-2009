package gov.nysenate.services.model;

public class Member {
	String name;
	String shortName;
	String url;
	
	public Member() {
		
	}
	
	public Member(String name, String shortName, String url) {
		this.name = name;
		this.shortName = shortName;
		this.url = url;
	}
	
	public Member(Senator senator) {
		this.name = senator.getName();
		this.shortName = senator.getShortName();
		this.url = senator.getUrl();
	}

	public String getName() {
		return name;
	}

	public String getShortName() {
		return shortName;
	}

	public String getUrl() {
		return url;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setShortName(String shortName) {
		this.shortName = shortName;
	}

	public void setUrl(String url) {
		this.url = url;
	}
}
