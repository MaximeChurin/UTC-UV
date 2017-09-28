package videoGameJPA;

import java.io.Serializable;
import javax.persistence.*;


/**
 * The persistent class for the contain database table.
 * 
 */
@Entity
@NamedQuery(name="Contain.findAll", query="SELECT c FROM Contain c")
public class Contain implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	private int quantity;

	//bi-directional many-to-one association to Game
	@ManyToOne
	@JoinColumn(name="fk_game")
	private Game game;

	//bi-directional many-to-one association to Purchase
	@ManyToOne
	@JoinColumn(name="fk_purchase")
	private Purchase purchase;

	public Contain() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public int getQuantity() {
		return this.quantity;
	}

	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}

	public Game getGame() {
		return this.game;
	}

	public void setGame(Game game) {
		this.game = game;
	}

	public Purchase getPurchase() {
		return this.purchase;
	}

	public void setPurchase(Purchase purchase) {
		this.purchase = purchase;
	}

}