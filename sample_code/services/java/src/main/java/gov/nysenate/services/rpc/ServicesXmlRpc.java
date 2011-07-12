package gov.nysenate.services.rpc;

import java.io.PrintStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.HashMap;
import java.util.List;

import org.apache.log4j.Logger;
import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;
import org.apache.xmlrpc.client.XmlRpcClientRequestImpl;
import org.apache.xmlrpc.client.XmlRpcCommonsTransportFactory;

public abstract class ServicesXmlRpc {
	private static Logger logger = Logger.getLogger(ServicesXmlRpc.class);
	
	protected String rpcUrl;
	
	public ServicesXmlRpc(String rpcUrl) {
		this.rpcUrl = rpcUrl;
	}
	
	public abstract Object getView(String viewName, String displayId, Integer offset,
			Integer limit, boolean formatOutput, List<Object> arguments);
	
	public abstract Object getNode(Integer nid);
	
	/* the following access the XmlRpc Apache library */

	public XmlRpcClient getXmlRpcClient(XmlRpcClientConfigImpl config) {
		XmlRpcClient client = new XmlRpcClient();
		client.setTransportFactory(new XmlRpcCommonsTransportFactory(client));
		client.setConfig(config);

		return client;
	}

	public Object getXmlRpcResponse(String methodName, List<Object> parameters) {
		XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
		
		try {
			config.setServerURL(new URL(rpcUrl));
			
			XmlRpcClientRequestImpl req = new XmlRpcClientRequestImpl(config,
					methodName, parameters);
			
			
			
			return getXmlRpcClient(config).execute(req);
			
		} catch (XmlRpcException e) {
			logger.warn(e);
		} catch (MalformedURLException e) {
			logger.warn(e);
		}
		
		return null;
	}
	
	public void print(Object object) {
		print(System.out, "", 0, object);
	}
	
	@SuppressWarnings("unchecked")
	public void print(PrintStream out, String path, int level, Object... objects) {
		for(Object object:objects) {
			if(object instanceof HashMap) {
				HashMap<String,Object> map = (HashMap<String,Object>) object;
				out.println(pad("\t", level) + "{");
				for(String key:map.keySet()) {
					Object temp = map.get(key);
					
					if(!path.contains(key) && key.contains("nid") && temp != null) {
						out.println(pad("\t", level + 1) + key + "(" + temp + ")");
						print(out, path + "." + key, level + 2, getNode(new Integer((String)temp)));
					}
					else if(isPrimitive(temp)) {
						out.println(pad("\t", level + 1) + key + ": " + temp.toString().replaceAll("\n"," "));
					}
					else {
						out.println(pad("\t", level + 1) + key);
						print(out, path, level + 2, temp);
					}
				}
				out.println(pad("\t", level) + "}");
			}
			else if(object instanceof Object[]) {
				out.println(pad("\t", level) + "[");
				
				Object[] objArr = (Object[]) object;
				int len = objArr.length;
				
				for(int i = 0; i < len; i++) {
					Object arrObj = objArr[i];
					out.println(pad("\t", level + 1) + i + " (");
					print(out, path, level + 2, arrObj);
					out.println(pad("\t", level + 1) + ")"
							 + (i < len - 1 ? "," : ""));
				}
				
				out.println(pad("\t", level) + "]");
			}
			else if(isPrimitive(object)) {
				out.println(pad("\t", level) + object.toString().replaceAll("\n"," "));
			}
			else {
				if(object == null) continue;
				
				out.println(object.getClass());
			}
		}
	}
	
	private String pad(String pad, int times) {
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < times; i++) {
			sb.append(pad);
		}
		return sb.toString();
	}
	
	private boolean isPrimitive(Object obj) {
		return obj != null && (
							   obj.getClass().isPrimitive()
							|| obj instanceof Boolean 
							|| obj instanceof Byte
							|| obj instanceof Character
							|| obj instanceof Double
							|| obj instanceof Float
							|| obj instanceof Integer
							|| obj instanceof Long
							|| obj instanceof Short
							|| obj instanceof String);
	}
}
