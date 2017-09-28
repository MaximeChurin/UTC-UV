package videoGameJPA;

import java.io.Serializable;
import javax.persistence.*;
import java.util.List;


/**
 * The persistent class for the console database table.
 * 
 */
@Entity
@NamedQuery(name="Console.findAll", query="SELECT c FROM Console c")
public class Console implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	private String name;

	//bi-directional many-to-one association to IsPlayedOn
	@OneToMany(mappedBy="console")
	private List<IsPlayedOn> isPlayedOns;

	public Console() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public List<IsPlayedOn> getIsPlayedOns() {
		return this.isPlayedOns;
	}

	public void setIsPlayedOns(List<IsPlayedOn> isPlayedOns) {
		this.isPlayedOns = isPlayedOns;
	}

	public IsPlayedOn addIsPlayedOn(IsPlayedOn isPlayedOn) {
		getIsPlayedOns().add(isPlayedOn);
		isPlayedOn.setConsole(this);

		return isPlayedOn;
	}

	public IsPlayedOn removeIsPlayedOn(IsPlayedOn isPlayedOn) {
		getIsPlayedOns().remove(isPlayedOn);
		isPlayedOn.setConsole(null);

		return isPlayedOn;
	}

}