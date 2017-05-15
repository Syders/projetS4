/**
 * 
 */
package HEX.src.jeu;

/**
 * @author Steven ISAMBERT-PAYET
 * @version 0.1
 * 
 */
public class Plateau {
	private int taille;
	private char tab[];
	private static InterfaceAvecC C=new InterfaceAvecC();
	public Plateau(int taille,char tab[]) {
		//super();
		this.taille = taille;
		for(int i=0;i<taille;i++){
			for(int j=0;j<taille;j++)
				this.tab[i*taille+j]=tab[i*taille+j];
		}
	}
	/**
	 * @author Steven ISAMBERT-PAYET
	 * @category Plateau\Affichage
	 * @param taille
	 * @param tab
	 */
	private void affichageTableau(){
		for(int i=0;i<taille;i++){
			System.out.println("W ");
		}
		System.out.println("W/B\n");
		for(int i=0;i<taille;i++){
			for(int k=0;k<=i;k++)System.out.println(" ");
			for(int j=0;i<taille;j++){
				if(j==0)System.out.println("B");
				System.out.println(tab[i*taille+j]);
			}
			System.out.println("B\n");
		}
		System.out.println("B/W ");
		for(int i=0;i<taille-1;i++){
			System.out.println("W ");
		}
		System.out.println("W\n * pour les noirs (B) et o pour les blancs (W) \n");
	}
	public int getTaille() {
		return taille;
	}
	
	private boolean verificationJoueurDebut(Information Joueur1,Information Joueur2){
		int J1=0,J2=0;
		for(int i=0;i<taille;i++){
			for(int j=0;j<taille;j++){
				if(tab[i*taille+j]==Joueur1.getPionDuJoueur())J1++;
				else if(tab[i*taille+j]==Joueur2.getPionDuJoueur())J2++;
			}
		}
		return J1<=J2;
	}
	
	
	public void jeu(Information Joueur1,Information Joueur2){
		Boolean quitter=false;
		Information JoueurActuelle;
		int action;
		if(verificationJoueurDebut(Joueur1,Joueur2))JoueurActuelle=Joueur1;
		else JoueurActuelle=Joueur2;
		do{
			JoueurActuelle.affichageInformation();
			action=C.action_joueur(tab,JoueurActuelle==Joueur1,taille);
			tab[action]=JoueurActuelle.getPionDuJoueur();
			affichageTableau();
			JoueurActuelle.setDernierCoupJoue(action);
			JoueurActuelle.changementNoTour();
		}while(C.gagnant(tab,taille)=='.' && !(quitter=C.question_quitter()));
		
		if(quitter){
			C.saveQuestion(tab,taille);
		}
	}
	
	
}
