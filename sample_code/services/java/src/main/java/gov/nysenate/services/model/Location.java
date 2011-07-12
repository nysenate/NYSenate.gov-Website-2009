package gov.nysenate.services.model;

public class Location {
	String name;
	
	String street;
	String city;
	String postalCode;
	String provinceName;
	String province;
	String countryName;
	String country;
	
	String phone;
	String fax;
	String otherPhone;
	String additional;
	
	double latitude;
	double longitude;
	
	public Location(String name, String street, String city,
			String postalCode, String provinceName, String province,
			String countryName, String country, String phone, String fax,
			String otherPhone, String additional, double latitude,
			double longitude) {
		
		this.name = name;
		this.street = street;
		this.city = city;
		this.postalCode = postalCode;
		this.provinceName = provinceName;
		this.province = province;
		this.countryName = countryName;
		this.country = country;
		this.phone = phone;
		this.fax = fax;
		this.otherPhone = otherPhone;
		this.additional = additional;
		this.latitude = latitude;
		this.longitude = longitude;
	}
	public String getName() {
		return name;
	}
	public String getStreet() {
		return street;
	}
	public String getCity() {
		return city;
	}
	public String getPostalCode() {
		return postalCode;
	}
	public String getProvinceName() {
		return provinceName;
	}
	public String getProvince() {
		return province;
	}
	public String getCountryName() {
		return countryName;
	}
	public String getCountry() {
		return country;
	}
	public String getPhone() {
		return phone;
	}
	public String getFax() {
		return fax;
	}
	public String getOtherPhone() {
		return otherPhone;
	}
	public String getAdditional() {
		return additional;
	}
	public double getLatitude() {
		return latitude;
	}
	public double getLongitude() {
		return longitude;
	}
	public void setName(String name) {
		this.name = name;
	}
	public void setStreet(String street) {
		this.street = street;
	}
	public void setCity(String city) {
		this.city = city;
	}
	public void setPostalCode(String postalCode) {
		this.postalCode = postalCode;
	}
	public void setProvinceName(String provinceName) {
		this.provinceName = provinceName;
	}
	public void setProvince(String province) {
		this.province = province;
	}
	public void setCountryName(String countryName) {
		this.countryName = countryName;
	}
	public void setCountry(String country) {
		this.country = country;
	}
	public void setPhone(String phone) {
		this.phone = phone;
	}
	public void setFax(String fax) {
		this.fax = fax;
	}
	public void setOtherPhone(String otherPhone) {
		this.otherPhone = otherPhone;
	}
	public void setAdditional(String additional) {
		this.additional = additional;
	}
	public void setLatitude(double latitude) {
		this.latitude = latitude;
	}
	public void setLongitude(double longitude) {
		this.longitude = longitude;
	}
}
