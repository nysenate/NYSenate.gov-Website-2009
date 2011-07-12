package gov.nysenate.services.model;

import java.util.ArrayList;

public class Committee {
	String name;
	String shortName;
	String url;
	ArrayList<Member> chairs;
	ArrayList<Member> members;
	
	public Committee() {
		this(null, null, null);
	}
	
	public Committee(String name, String shortName, String url) {
		this(name, shortName, url, new ArrayList<Member>(), new ArrayList<Member>());
	}
	
	public Committee(String name, String shortName, String url,
				ArrayList<Member> chairs, 
				ArrayList<Member> members) {
		
		this.name = name;
		this.shortName = shortName;
		this.url = url;
		this.chairs = chairs;
		this.members = members;
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

	public ArrayList<Member> getChairs() {
		return chairs;
	}

	public ArrayList<Member> getMembers() {
		return members;
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

	public void setChairs(ArrayList<Member> chairs) {
		this.chairs = chairs;
	}

	public void setMembers(ArrayList<Member> members) {
		this.members = members;
	}
	
	public void addMember(Member member) {
		this.members.add(member);
	}
	
	public void addChair(Member member) {
		this.chairs.add(member);
	}
}
