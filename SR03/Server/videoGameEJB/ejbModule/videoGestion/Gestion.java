package videoGestion;

import java.util.List;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.OneToMany;
import javax.persistence.PersistenceContext;

import videoGameJPA.Game;
import videoGameJPA.Console;
import videoGameJPA.IsPlayedOn;
import videoGameJPA.LiveIn;
import videoGameJPA.Purchase;
import videoGameJPA.Customer;


@Stateless
public class Gestion implements GestionLocal {
	@PersistenceContext(unitName="videoGameJPA")
	private EntityManager em;
	
	public List<Game> findAllGames() {
		List<Game> resultsList = em.createQuery("SELECT g FROM Game g").getResultList();
		for(int i = 0; i < resultsList.size(); i++) {
			resultsList.get(i).setContains(null);
			resultsList.get(i).setIsPlayedOns(null);
		}

		return resultsList;
	}
	
	public Game findGameById(int id) {
		Game result = em.find(Game.class, id);
		if(null != result) {			
			result.setContains(null);
			result.setIsPlayedOns(null);
		}

		return result;
	}
	
	public List<IsPlayedOn> findAllIsPlayedOn() {
		List<IsPlayedOn> resultsList = em.createQuery("SELECT i FROM IsPlayedOn i").getResultList();

		return resultsList;
	}
	
	public List<IsPlayedOn> findAllConsoleNamesFromIsPlayedOnsByGame(Game currentGame) {
		List<IsPlayedOn> resultsList =
			em.createQuery("SELECT i.console.name FROM IsPlayedOn i WHERE i.game = :currentgame")
			.setParameter("currentgame", currentGame)
			.getResultList();

		return resultsList;
	}
	
	public List<Console> findAllConsoles() {
		List<Console> resultsList = em.createQuery("SELECT c.id, c.name FROM Console c").getResultList();

		return resultsList;
	}
	
	public List<Game> findAllGamesWithConsoles() {
		List<Game> listGames = findAllGames();
		List<IsPlayedOn> consoleNames = null;
		for(int i = 0; i < listGames.size(); i++) {
			consoleNames = findAllConsoleNamesFromIsPlayedOnsByGame(listGames.get(i));
			listGames.get(i).setIsPlayedOns(consoleNames);
		}

		return listGames;
	}

	public Game findGameWithConsolesById(int id) {
		Game result = findGameById(id);

		if(null != result) {			
			List<IsPlayedOn> consoleNames = findAllConsoleNamesFromIsPlayedOnsByGame(result);
			result.setIsPlayedOns(consoleNames);
		}

		return result;
	}
	
	public Customer findCustomerByEmailAndPassword(String customerEmail, String customerPassword) {
		Customer result = (Customer) em.createQuery("SELECT c FROM Customer c WHERE c.email = :customeremail AND c.password = :customerpassword").setParameter("customeremail", customerEmail).setParameter("customerpassword", customerPassword).getSingleResult();
		result.setLiveIns(null);
		result.setPurchases(null);

		return result;
	}
}
