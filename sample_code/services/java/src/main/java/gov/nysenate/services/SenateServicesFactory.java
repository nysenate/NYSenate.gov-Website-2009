package gov.nysenate.services;

import gov.nysenate.services.rpc.SenateServicesXmlRpc;

public class SenateServicesFactory {
	public SenateServicesDAO createSenateServicesDAO(String apiKey) {
		SenateServicesXmlRpc rpc = new SenateServicesXmlRpc(
				"http://www.nysenate.gov/services/xmlrpc", "nysenate.gov", apiKey);
		return new SenateServicesDAO(rpc);
	}
}