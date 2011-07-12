package gov.nysenate.services.model;

import java.util.ArrayList;

public class Senator {
	String name;
	String lastName;
	String shortName;
	
	String email;
	String additionalContact;
	
	String imageUrl;
	
	String url;

	ArrayList<String> partyAffiliations;
	
	Geo geo;
	
	Social social;
	
	public Senator() {
		this(null, null, null, null, null, null, null);
	}
	
	public Senator(String name, String lastName, String shortName,
			String email, String additionalContact, String imageUrl, String url) {
		this(name, lastName, shortName, email, additionalContact, imageUrl, url,
				new Geo(), new Social(), new ArrayList<String>());
	}
	
	public Senator(String name, String lastName, String shortName,
			String email, String additionalContact, String imageUrl, String url, 
			Geo geo, Social social, ArrayList<String> partyAffiliations) {
		this.name = name;
		this.lastName = lastName;
		this.shortName = shortName;
		
		this.email = email;
		this.additionalContact = additionalContact;
		
		this.imageUrl = imageUrl;
		
		this.url = url;
		
		this.partyAffiliations = partyAffiliations;
		
		this.geo = geo;
		
		this.social = social;
	}

	public String getName() {
		return name;
	}

	public String getLastName() {
		return lastName;
	}

	public String getShortName() {
		return shortName;
	}

	public String getEmail() {
		return email;
	}

	public String getAdditionalContact() {
		return additionalContact;
	}

	public ArrayList<String> getPartyAffiliations() {
		return partyAffiliations;
	}
	
	public String getImageUrl() {
		return imageUrl;
	}

	public String getUrl() {
		return url;
	}

	public Geo getGeo() {
		return geo;
	}

	public Social getSocial() {
		return social;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public void setShortName(String shortName) {
		this.shortName = shortName;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public void setAdditionalContact(String additionalContact) {
		this.additionalContact = additionalContact;
	}

	public void setPartyAffiliations(ArrayList<String> partyAffiliations) {
		this.partyAffiliations = partyAffiliations;
	}
	
	public void setImageUrl(String imageUrl) {
		this.imageUrl = imageUrl;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public void setGeo(Geo geo) {
		this.geo = geo;
	}

	public void setSocial(Social social) {
		this.social = social;
	}
	
	public void addPartyAffiliation(String affiliation) {
		this.partyAffiliations.add(affiliation);
	}
}
