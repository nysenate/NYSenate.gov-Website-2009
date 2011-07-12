package gov.nysenate.services.model;

public class District {
	int number;
	String imageUrl;
	String mapUrl;
	
	public District() {
		
	}
	
	public District(int number, String imageUrl, String mapUrl) {
		this.number = number;
		this.imageUrl = imageUrl;
		this.mapUrl = mapUrl;
	}

	public int getNumber() {
		return number;
	}

	public String getImageUrl() {
		return imageUrl;
	}

	public String getMapUrl() {
		return mapUrl;
	}

	public void setNumber(int number) {
		this.number = number;
	}

	public void setImageUrl(String imageUrl) {
		this.imageUrl = imageUrl;
	}

	public void setMapUrl(String mapUrl) {
		this.mapUrl = mapUrl;
	}
}
