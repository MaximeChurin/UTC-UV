package videoGameJPA;

import java.io.Serializable;
import javax.persistence.*;
import java.util.List;


/**
 * The persistent class for the adress database table.
 * 
 */
@Entity
@NamedQuery(name="Adress.findAll", query="SELECT a FROM Adress a")
public class Adress implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	private String adress;

	private String country;

	@Column(name="zip_code")
	private int zipCode;

	//bi-directional many-to-one association to LiveIn
	@OneToMany(mappedBy="adress")
	private List<LiveIn> liveIns;

	//bi-directional many-to-one association to Purchase
	@OneToMany(mappedBy="adress")
	private List<Purchase> purchases;

	public Adress() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getAdress() {
		return this.adress;
	}

	public void setAdress(String adress) {
		this.adress = adress;
	}

	public String getCountry() {
		return this.country;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	public int getZipCode() {
		return this.zipCode;
	}

	public void setZipCode(int zipCode) {
		this.zipCode = zipCode;
	}

	public List<LiveIn> getLiveIns() {
		return this.liveIns;
	}

	public void setLiveIns(List<LiveIn> liveIns) {
		this.liveIns = liveIns;
	}

	public LiveIn addLiveIn(LiveIn liveIn) {
		getLiveIns().add(liveIn);
		liveIn.setAdress(this);

		return liveIn;
	}

	public LiveIn removeLiveIn(LiveIn liveIn) {
		getLiveIns().remove(liveIn);
		liveIn.setAdress(null);

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
		purchas.setAdress(this);

		return purchas;
	}

	public Purchase removePurchas(Purchase purchas) {
		getPurchases().remove(purchas);
		purchas.setAdress(null);

		return purchas;
	}

}