/**
 * 
 */
package HEX.src.jeu;

/**
 * @author Steven ISAMBERT-PAYET
 * @version 0.1
 *
 */
public class Main {
	
	private static InterfaceAvecC C=new InterfaceAvecC();
	
	private static void menuPrincipal(){
		System.out.println("HEX Version 0.1 \n\nVoulez-vous commencer une partie?[Taper 1]");
		if(C.saveDisponible())
			menuSaveDisponible();
		System.out.println(" ou quitter le jeu [Taper 3]");
	}
	
	private static void menuSaveDisponible(){
		System.out.println(" ou charger la partie en cours [Taper 2] ");
	}
	
	private static void choixDesPions(int noJoueur){
		System.out.println("Joueur n°" + noJoueur + " choisissez votre pion. Le joueur 2 aura l'autre pion. [soit b pour black ou w pour white]\n");
	}
	
	private static void choixTaille(){
		System.out.println("Choisissez la taille du plateau:\n");
	}


	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
			menuPrincipal();
			//inserer un choix
			int choix=C.choix_mode();
			Information Joueur1;
			Information Joueur2;
			int size;
			char plateau [];
			Plateau main;
			if(choix==1){
				choixDesPions(1);
				Joueur1=new Information(1,C.creer_information_joueur_1());
				//pion n°2 sera donc l'autre
				if(Joueur1.getPionDuJoueur()=='*')
					Joueur2=new Information(2,'o');
				else
					Joueur2=new Information(2,'*');
				choixTaille();
				size=C.choixTaille();
				plateau=C.initialisationTab(size);
				main=new Plateau(size,plateau);
			}else if(choix==2){
				//On demande quand même quelle était les pions des joueurs 
				choixDesPions(1);
				Joueur1=new Information(1,C.creer_information_joueur_1());
				if(Joueur1.getPionDuJoueur()=='*')
					Joueur2=new Information(2,'o');
				else
					Joueur2=new Information(2,'*');
				main=new Plateau(C.loadSaveSize(),C.loadSaveTab());
			}else return;	
			//jeu
			main.jeu(Joueur1,Joueur2);
			
	}

}
