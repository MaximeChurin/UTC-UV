package videoGestion;

import java.util.List;

import javax.ejb.Local;

import videoGameJPA.Game;
import videoGameJPA.IsPlayedOn;
import videoGameJPA.Console;
import videoGameJPA.Customer;

@Local
public interface GestionLocal {
	public List<Game> findAllGames();
	public List<IsPlayedOn> findAllIsPlayedOn();
	public List<Console> findAllConsoles();
	public List<Game> findAllGamesWithConsoles();
	public Game findGameWithConsolesById(int id);
	public Customer findCustomerByEmailAndPassword(String customerEmail, String customerPassword);
}
