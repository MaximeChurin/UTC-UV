package videoGameJPA;

import java.io.Serializable;
import javax.persistence.*;


/**
 * The persistent class for the live_in database table.
 * 
 */
@Entity
@Table(name="live_in")
@NamedQuery(name="LiveIn.findAll", query="SELECT l FROM LiveIn l")
public class LiveIn implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	//bi-directional many-to-one association to Adress
	@ManyToOne
	@JoinColumn(name="fk_adress")
	private Adress adress;

	//bi-directional many-to-one association to Customer
	@ManyToOne
	@JoinColumn(name="fk_customer")
	private Customer customer;

	public LiveIn() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public Adress getAdress() {
		return this.adress;
	}

	public void setAdress(Adress adress) {
		this.adress = adress;
	}

	public Customer getCustomer() {
		return this.customer;
	}

	public void setCustomer(Customer customer) {
		this.customer = customer;
	}

}