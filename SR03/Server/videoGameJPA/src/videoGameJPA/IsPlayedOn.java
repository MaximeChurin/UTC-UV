package videoGameJPA;

import java.io.Serializable;
import javax.persistence.*;


/**
 * The persistent class for the is_played_on database table.
 * 
 */
@Entity
@Table(name="is_played_on")
@NamedQuery(name="IsPlayedOn.findAll", query="SELECT i FROM IsPlayedOn i")
public class IsPlayedOn implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	//bi-directional many-to-one association to Console
	@ManyToOne
	@JoinColumn(name="fk_console")
	private Console console;

	//bi-directional many-to-one association to Game
	@ManyToOne
	@JoinColumn(name="fk_game")
	private Game game;

	public IsPlayedOn() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public Console getConsole() {
		return this.console;
	}

	public void setConsole(Console console) {
		this.console = console;
	}

	public Game getGame() {
		return this.game;
	}

	public void setGame(Game game) {
		this.game = game;
	}

}