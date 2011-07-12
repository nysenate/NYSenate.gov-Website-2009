package gov.nysenate.services.main;

import java.util.ArrayList;
import java.util.HashMap;

import org.apache.log4j.Logger;

import gov.nysenate.services.model.Committee;
import gov.nysenate.services.model.District;
import gov.nysenate.services.model.Geo;
import gov.nysenate.services.model.Location;
import gov.nysenate.services.model.Member;
import gov.nysenate.services.model.Senator;
import gov.nysenate.services.model.Social;
import gov.nysenate.services.rpc.ServicesXmlRpc;

/**
 * SenateServicesFactory factory = new SenateServicesFactory();
 * SenateServicesDao = factory.createSenateServicesDao(<your api key>);
 * etc.
 *
 */
public class SenateServicesDAO {
	public static final String BASE_URL = "http://www.nysenate.gov/";
	
	private static Logger logger = Logger.getLogger(SenateServicesDAO.class);
	
	protected ServicesXmlRpc rpc;
	
	private HashMap<Integer, Object> nodeCache;
	
	public SenateServicesDAO(ServicesXmlRpc rpc) {
		this.rpc = rpc;
		nodeCache = new HashMap<Integer, Object>();
	}
	
	public void fillCache(Integer id, Object obj) {
		nodeCache.put(id, obj);
	}
	
	@SuppressWarnings("unchecked")
	public <T> T getCache(Integer id) {
		return (T) nodeCache.get(id);
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList<Committee> getCommittees() {
		logger.info("Geting committees view");
		
		Object view = rpc.getView("committees", "block_1", null,
				null, false, null);
		Object[] committeeObjects = as(Object[].class, view);
		
		ArrayList<Committee> committees = new ArrayList<Committee>();
		
		for(Object committee:committeeObjects) {
			HashMap<String,Object> committeeMap = as(HashMap.class, committee);
			
			committees.add(getCommittee(new Integer(as(String.class,committeeMap.get("nid")))));
		}
		
		return committees;
	}
	
	@SuppressWarnings("unchecked")
	public Committee getCommittee(int nodeId) {
		Committee committee = getCache(nodeId);
		if(committee != null) {
			logger.info("Got cached committee - " + committee.getName());
			return committee;
		}
		
		Object node = rpc.getNode(nodeId);
		HashMap<String,Object> committeeMap = as(HashMap.class, node);
		
		if(committeeMap == null) return null;
		
		if(!as(String.class,committeeMap.get("type")).equals("committee"))
			return null;
		
		String name = as(String.class, committeeMap.get("title"));
		String shortName = unwrap(String.class, committeeMap.get("field_short_name"), "value");
		String url = BASE_URL + as(String.class, committeeMap.get("path"));
		
		ArrayList<Member> members = new ArrayList<Member>();
		
		Object[] memberObjects = as(Object[].class, committeeMap.get("field_multi_senator"));
		for(Object object:memberObjects) {
			HashMap<String,Object> multiSenatorMap = as(HashMap.class, object);
			
			int memberNodeId = new Integer(as(String.class, multiSenatorMap.get("nid")));
			
			members.add(new Member(getSenator(memberNodeId)));
		}
		
		ArrayList<Member> chairs = new ArrayList<Member>();
		
		Object[] chairObjects = as(Object[].class, committeeMap.get("field_chairs"));
		for(Object object:chairObjects) {
			HashMap<String,Object> chairMap = as(HashMap.class, object);
			
			int memberNodeId = new Integer(as(String.class, chairMap.get("nid")));
			
			chairs.add(new Member(getSenator(memberNodeId)));
		}
		
		logger.info("Got node id: " + nodeId + " for committee " + name);
		
		committee = new Committee(name, shortName, url, chairs, members);
		fillCache(nodeId, committee);
		
		return committee;
	}
	
	
	
	@SuppressWarnings("unchecked")
	public ArrayList<Senator> getSenators() {
		logger.info("Geting senators view");
		
		Object view = rpc.getView("senators", null, null,
				null, false, null);
		Object[] senatorObjects = as(Object[].class, view);
		
		ArrayList<Senator> senators = new ArrayList<Senator>();
		
		for(Object senator:senatorObjects) {
			HashMap<String,Object> senatorMap = as(HashMap.class, senator);
			
			senators.add(getSenator(new Integer(as(String.class,senatorMap.get("nid")))));
		}
		
		return senators;
	}
	
	@SuppressWarnings("unchecked")
	public Senator getSenator(int nodeId) {
		Senator senator = getCache(nodeId);
		if(senator != null) {
			logger.info("Got cached senator " + senator.getName());
			return senator;
		}
		
		Object node = rpc.getNode(nodeId);
		HashMap<String,Object> senatorMap = as(HashMap.class, node);
		
		if(senatorMap == null) return null;
		
		if(!as(String.class,senatorMap.get("type")).equals("senator"))
			return null;
		
		String name = as(String.class, senatorMap.get("title"));
				
		String lastName = unwrap(String.class, senatorMap.get("field_last_name"), "value");
		String shortName = unwrap(String.class, senatorMap.get("field_short_name"), "value");
		
		String email = unwrap(String.class, senatorMap.get("field_email"), "email");
		String additionalContact = unwrap(String.class, senatorMap.get("field_extra_contact_information"), "value");
		
		String url = BASE_URL + as(String.class, senatorMap.get("path"));
		
		String imageUrl = BASE_URL + unwrap(String.class, senatorMap.get("field_profile_picture"), "filepath");
		
		ArrayList<String> partyAffiliations = new ArrayList<String>();

		Object[] partyObjects = as(Object[].class, senatorMap.get("field_party_affiliation"));
		for(Object object:partyObjects) {
			HashMap<String,Object> partyAffilationMap = as(HashMap.class, object);
			String value = as(String.class, partyAffilationMap.get("value"));
			
			if(!value.matches("\\s*"))
				partyAffiliations.add(value);
		}
		
		logger.info("Got node id: " + nodeId + " for senator " + name);
		
		senator = new Senator(name, lastName, shortName, email, additionalContact, 
				imageUrl, url, getGeo(senatorMap), getSocial(senatorMap), partyAffiliations);
		
		fillCache(nodeId, senator);
		
		return senator;
	}
	
	@SuppressWarnings("unchecked")
	private Geo getGeo(HashMap<String,Object> senatorMap) {
		String districtNodeId = unwrap(String.class, senatorMap.get("field_senators_district"), "nid");
		HashMap<String,Object> districtMap = as(HashMap.class, rpc.getNode(new Integer(districtNodeId)));
		
		int districtNumber = new Integer(unwrap(String.class, districtMap.get("field_district_number"), "value"));
		String districtImageUrl = BASE_URL + unwrap(String.class, districtMap.get("field_district_map"),"filepath");
		String districtSageUrl = unwrap(String.class, districtMap.get("field_sage_map"),"url");
		
		ArrayList<Location> locations = new ArrayList<Location>();
		
		Object[] officeLocations = as(Object[].class, senatorMap.get("locations"));
		for(Object object:officeLocations) {
			HashMap<String,String> locationMap = as(HashMap.class, object);
			
			String name = as(String.class, locationMap.get("name"));
			
			String street = as(String.class, locationMap.get("street"));
			String city = as(String.class, locationMap.get("city"));
			String postalCode = as(String.class, locationMap.get("postal_code"));
			String provinceName = as(String.class, locationMap.get("province_name"));
			String province = as(String.class, locationMap.get("province"));
			String countryName = as(String.class, locationMap.get("country_name"));
			String country = as(String.class, locationMap.get("country"));
			
			String phone = as(String.class, locationMap.get("phone"));
			String fax = as(String.class, locationMap.get("fax"));
			String otherPhone = as(String.class, locationMap.get("otherphone"));
			String additional = as(String.class, locationMap.get("additional"));
			
			double latitude = new Double(as(String.class, locationMap.get("latitude")));
			double longitude = new Double(as(String.class, locationMap.get("longitude")));
			
			locations.add(new Location(name, street, city, postalCode, 
					provinceName, province, countryName, country, phone, 
					fax, otherPhone, additional, latitude, longitude));
		}
		
		return new Geo(new District(districtNumber, districtImageUrl, districtSageUrl), locations);
	}
	
	private Social getSocial(HashMap<String,Object> senatorMap) {
		String twitter = unwrap(String.class, senatorMap.get("field_twitter_link"), "url");
		String youtube = unwrap(String.class, senatorMap.get("field_youtube_link"), "url");
		String myspace = unwrap(String.class, senatorMap.get("field_myspace_link"), "url");
		String picasa = unwrap(String.class, senatorMap.get("field_picasa_link"), "url");
		String flickr = unwrap(String.class, senatorMap.get("field_flickr_link"), "url");
		String facebook = unwrap(String.class, senatorMap.get("field_facebook_link"), "url");
		
		return new Social(twitter, youtube, myspace, picasa, flickr, facebook);
	}
	
	@SuppressWarnings("unchecked")
	private <T> T unwrap(Class<T> clazz, Object object, String key) {
		return as(clazz, ((HashMap<String,Object>)((Object[])object)[0]).get(key));
	}
	
	@SuppressWarnings("unchecked")
	public <T> T as(Class<T> clazz, Object object) {
		if(object != null && clazz != null && clazz.isInstance(object)) 
			return (T) object;
		return null;
	}
}
