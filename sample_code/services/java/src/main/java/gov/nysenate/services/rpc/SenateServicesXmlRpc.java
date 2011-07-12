package gov.nysenate.services.rpc;

import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

import org.apache.log4j.Logger;

public class SenateServicesXmlRpc extends ServicesXmlRpc {
	public static final String NODE_GET = "node.get";
	public static final String VIEWS_GET = "views.get";
	
	private static Logger logger = Logger.getLogger(SenateServicesXmlRpc.class);
	
	protected String baseUrl;
	protected String apiKey;
	
	public SenateServicesXmlRpc(String rpcUrl, String baseUrl,  String apiKey) {
		super(rpcUrl);
		this.baseUrl = baseUrl;
		this.apiKey = apiKey;
	}
	
	/**
	 * 
	 * @param viewName
	 *            required
	 * @param displayId
	 * @param offset
	 * @param limit
	 *            max results to return
	 * @param formatOutput
	 *            false should be default, true will return html formatted
	 *            response
	 * @param arguments
	 *            list of optional arguments
	 * @return object from XmlRpc request
	 */
	public Object getView(String viewName, String displayId, Integer offset,
			Integer limit, boolean formatOutput, List<Object> arguments) {

		List<Object> params = new ArrayList<Object>();
		params.addAll(getSecurityParameters(VIEWS_GET));
		params.add(viewName);
		params.add((displayId == null) ? "default" : displayId);

		if (arguments == null) {
			arguments = new ArrayList<Object>();
		}
		params.add(arguments);

		params.add((offset == null) ? 0 : offset);
		params.add((limit == null) ? 0 : limit);
		params.add(formatOutput);

		return getXmlRpcResponse(VIEWS_GET, params);
	}
	
	/**
	 * @param nid
	 *            node id
	 * @return object from XmlRpc request
	 */
	public Object getNode(Integer nid) {
		List<Object> params = new ArrayList<Object>();
		params.addAll(getSecurityParameters(NODE_GET));
		params.add(nid);

		return getXmlRpcResponse(NODE_GET, params);
	}
	
	/**
	 * @return returns list of parameters that must be tied to ever services
	 *         XmlRpc request
	 */
	public List<Object> getSecurityParameters(String methodName) {
		long time = (new Date()).getTime();
		String nonce = generateServiceNonce(time);
		String hash = generateServicesHash(time, nonce, methodName);
		
		List<Object> params = new ArrayList<Object>();
		params.add(hash);
		params.add(baseUrl);
		params.add(time + "");
		params.add(nonce);

		return params;
	}

	public String generateServiceNonce(long time) {
		String nonce = null;

		try {
			MessageDigest md = MessageDigest.getInstance("MD5");
			
			byte[] md5Digest = md.digest(Long.toString(time).getBytes());

			nonce = "";
			for (byte b : md5Digest) {
				nonce += String.format("%02x", b);
			}
			
			return nonce.substring(0, 20);
			
		} catch (NoSuchAlgorithmException e) {
			logger.error(e);
		}

		return nonce;
	}

	public String generateServicesHash(long time, String nonce,
			String methodName) {
		String hash = null;

		Mac mac;
		try {
			mac = Mac.getInstance("HmacSHA256");
			
			SecretKeySpec secret = new SecretKeySpec(
					apiKey.getBytes(),"HmacSHA256");
			
			mac.init(secret);
		
			byte[] shaDigest = mac.doFinal(
						(time + ";" +
						baseUrl + ";" +
						nonce + ";" +
						methodName).getBytes());
			
			hash = "";
			
			for (byte b : shaDigest) {
				hash += String.format("%02x", b);
			}
			
		} catch (NoSuchAlgorithmException e) {
			logger.error(e);
		} catch (InvalidKeyException e) {
			logger.error(e);
		}

		return hash;
	}
}
