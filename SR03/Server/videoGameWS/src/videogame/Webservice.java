package videogame;

import java.util.List;

import javax.ejb.EJB;
import javax.ejb.Stateless;
import javax.jws.WebParam;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import videoGameJPA.Game;
import videoGameJPA.Customer;

@Stateless 
@Path("/jeux")
@Consumes(MediaType.APPLICATION_JSON)
@Produces(MediaType.APPLICATION_JSON + "; charset=UTF-8")
public class Webservice {
	@EJB
	public videoGestion.GestionLocal vgEjb;
	
	@GET
	@Path("/")
	public Response getAllGames(){
		//http://localhost:8080/videoGameWS/rest/jeux/
		List<Game> listResult= vgEjb.findAllGamesWithConsoles();		
		return Response.ok(listResult).build();
	}
	
	@GET
	@Path("/id/{id}")
	public Response getGameById(@PathParam("id") int id){
		//http://localhost:8080/videoGameWS/rest/jeux/id/1
		String response = null;
		
		Game listResult= vgEjb.findGameWithConsolesById(id);
		
		if(null == listResult) {
			response = "Game - id : "+ id +" - Not Found in Database";
			return Response.status(404).entity(response).build();
		}
		
		return Response.ok(listResult).build();
	}
	
	@GET
	@Path("/customer")
	public Response Connection(@QueryParam("email") String email, @QueryParam("password") String password){
		//http://localhost:8080/videoGameWS/rest/jeux/customer?email=max@gmail.com&password=mdp
		String response = null;
		try {
			Customer existingCustomer = vgEjb.findCustomerByEmailAndPassword(email, password);
			if(null == existingCustomer){
				response = "Customer - email : "+ email + " - Not Found in Database";
				return Response.status(404).entity(response).build();
			}
			return Response.ok(existingCustomer).build();
			//return Response.status(200).entity("Okay").build();
		} catch (Exception err) {
			response = "{\"status\":\"401\","
					+ "\"message\":\"No content found \""
					+ "\"developerMessage\":\"" + err.getMessage() + "\"" + "}";
			return Response.status(401).entity(response).build();
		}	
	}
}