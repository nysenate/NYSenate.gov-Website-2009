package gov.nysenate.services.model;

import java.util.ArrayList;

public class Geo {
	District district;
	
	ArrayList<Location> locations;
	
	public Geo() {
		this(null);
	}
	
	public Geo(District district) {
		this(district, new ArrayList<Location>());
	}
	
	public Geo(District district, ArrayList<Location> locations) {
		this.district = district;
		this.locations = locations;
	}

	public District getDistrict() {
		return district;
	}

	public ArrayList<Location> getLocations() {
		return locations;
	}

	public void setDistrict(District district) {
		this.district = district;
	}

	public void setLocations(ArrayList<Location> locations) {
		this.locations = locations;
	}
	
	public void addLocation(Location location) {
		this.locations.add(location);
	}
}