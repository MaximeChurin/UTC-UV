package videoGameJPA;

import java.io.Serializable;
import javax.persistence.*;
import java.util.List;


/**
 * The persistent class for the game database table.
 * 
 */
@Entity
@NamedQuery(name="Game.findAll", query="SELECT g FROM Game g")
public class Game implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	private float price;

	private String title;

	//bi-directional many-to-one association to Contain
	@OneToMany(mappedBy="game")
	private List<Contain> contains;

	//bi-directional many-to-one association to IsPlayedOn
	@OneToMany(mappedBy="game")
	private List<IsPlayedOn> isPlayedOns;

	public Game() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public float getPrice() {
		return this.price;
	}

	public void setPrice(float price) {
		this.price = price;
	}

	public String getTitle() {
		return this.title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public List<Contain> getContains() {
		return this.contains;
	}

	public void setContains(List<Contain> contains) {
		this.contains = contains;
	}

	public Contain addContain(Contain contain) {
		getContains().add(contain);
		contain.setGame(this);

		return contain;
	}

	public Contain removeContain(Contain contain) {
		getContains().remove(contain);
		contain.setGame(null);

		return contain;
	}

	public List<IsPlayedOn> getIsPlayedOns() {
		return this.isPlayedOns;
	}

	public void setIsPlayedOns(List<IsPlayedOn> isPlayedOns) {
		this.isPlayedOns = isPlayedOns;
	}

	public IsPlayedOn addIsPlayedOn(IsPlayedOn isPlayedOn) {
		getIsPlayedOns().add(isPlayedOn);
		isPlayedOn.setGame(this);

		return isPlayedOn;
	}

	public IsPlayedOn removeIsPlayedOn(IsPlayedOn isPlayedOn) {
		getIsPlayedOns().remove(isPlayedOn);
		isPlayedOn.setGame(null);

		return isPlayedOn;
	}

}