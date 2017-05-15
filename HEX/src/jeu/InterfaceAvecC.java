/**
 * 
 */
package HEX.src.jeu;

/**
 * @author Steven ISAMBERT-PAYET
 * @version 0.1
 *
 */
public class InterfaceAvecC {
	public native int choix_mode();
	public native Boolean saveDisponible();
	public native char creer_information_joueur_1();
	public native int choixTaille();
	public native char[] initialisationTab(int size);
	public native int loadSaveSize();
	public native char[] loadSaveTab();
	public native int action_joueur(char [] tab,Boolean joueur,int size);
	public native Boolean question_quitter();
	public native char gagnant(char [] tab, int size);
	public native void saveQuestion(char [] tab, int size);
	static {
		System.loadLibrary("mabibjni");
	}
}
