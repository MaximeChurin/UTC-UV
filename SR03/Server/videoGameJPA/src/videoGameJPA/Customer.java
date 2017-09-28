package videoGameJPA;

import java.io.Serializable;
import javax.persistence.*;
import java.util.List;


/**
 * The persistent class for the customer database table.
 * 
 */
@Entity
@NamedQuery(name="Customer.findAll", query="SELECT c FROM Customer c")
public class Customer implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	private String email;

	@Column(name="first_name")
	private String firstName;

	@Column(name="last_name")
	private String lastName;

	private String password;

	@Column(name="phone_number")
	private String phoneNumber;

	//bi-directional many-to-one association to LiveIn
	@OneToMany(mappedBy="customer")
	private List<LiveIn> liveIns;

	//bi-directional many-to-one association to Purchase
	@OneToMany(mappedBy="customer")
	private List<Purchase> purchases;

	public Customer() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getEmail() {
		return this.email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getFirstName() {
		return this.firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return this.lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getPassword() {
		return this.password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getPhoneNumber() {
		return this.phoneNumber;
	}

	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}

	public List<LiveIn> getLiveIns() {
		return this.liveIns;
	}

	public void setLiveIns(List<LiveIn> liveIns) {
		this.liveIns = liveIns;
	}

	public LiveIn addLiveIn(LiveIn liveIn) {
		getLiveIns().add(liveIn);
		liveIn.setCustomer(this);

		return liveIn;
	}

	public LiveIn removeLiveIn(LiveIn liveIn) {
		getLiveIns().remove(liveIn);
		liveIn.setCustomer(null);

		return liveIn;
	}

	public List<Purchase> getPurchases() {
		return this.purchases;
	}

	public void setPurchases(List<Purchase> purchases) {
		this.purchases = purchases;
	}

	public Purchase addPurchas(Purchase purchas) {
		getPurchases().add(purchas);
		purchas.setCustomer(this);

		return purchas;
	}

	public Purchase removePurchas(Purchase purchas) {
		getPurchases().remove(purchas);
		purchas.setCustomer(null);

		return purchas;
	}

}