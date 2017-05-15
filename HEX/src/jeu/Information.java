/**
 * 
 */
package HEX.src.jeu;

/**
 * @author Steven ISAMBERT-PAYET
 * @version 0.1
 *
 */
public class Information {
	private int noJoueur;
	private int noTour;
	private int dernierCoupJoue;
	private int noCoup;
	private char pionDuJoueur;
	public Information(int noJoueur, char pionDuJoueur) {
		//super();
		this.noJoueur = noJoueur;
		this.noTour = 1;
		this.dernierCoupJoue = 0;
		this.noCoup = 0;
		this.pionDuJoueur = pionDuJoueur;
	}
	
	public int getNoJoueur() {
		return noJoueur;
	}

	public char getPionDuJoueur() {
		return pionDuJoueur;
	}

	public void affichageInformation(){
		System.out.println(" Joueur n°" + noJoueur + "\n Tour n°" + noTour + "\n Dernier Coup Joué: Case n°" + dernierCoupJoue + "\n Coup du Joueur n°" + noCoup + "\n Pion du Joueur: " + pionDuJoueur + "\n" );
	}
	
	
	public void setDernierCoupJoue(int dernierCoupJoue) {
		this.dernierCoupJoue = dernierCoupJoue;
	}

	public void changementNoTour (){
		noCoup++;
		noTour=noTour+2;
	}
	
	public void menuJeu(){
		System.out.println("Joueur n°" + noJoueur + "votre action.\n");
	}
	
}
