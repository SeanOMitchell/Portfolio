//Main class
class Office {
	
	//Main program
	public static void main(String[] args){
		//Declaring new buffers for use as the tray and executive lounge
		Tray letterTray = new Tray();
		Lounge execLounge = new Lounge();
		//Declaring new worker threads for use as secretaries
		Worker secA = new Worker('A', 1, 12, letterTray);
		Worker secB = new Worker('B', 2, 8, letterTray);
		Worker secC = new Worker('C', 6, 4, letterTray);
		Worker secD = new Worker('D', 6, 4, letterTray);
		//Declaring new manager threads for each of the managers
		Manager ManA = new Manager('A', 2, 20, 19, letterTray, execLounge);
		Manager ManB = new Manager('B', 4, 60, 9, letterTray, execLounge);
		//Start each thread running
		secA.start();
		secB.start();
		secC.start();
		secD.start();
		ManA.start();
		ManB.start();
  }
}

//Worker thread for use as secretaries
class Worker extends Thread{
	//Storing the letter ascociated with the secretary
	private char secID;
	//Storing the secretary's typing speed, quota and how the current letter being typed
	private int speed, letterQuota, letterCount = 1;
	//Allows the secretary to access the Tray
	Tray letterTray;
	//Constructor method
	public Worker(char secretaryID, int secSpeed, int secQuota, Tray officeTray){
		//Passing parameters to the local variables
		secID = secretaryID;
		speed = secSpeed;
		letterQuota = secQuota;
		letterTray = officeTray;
	}
	public void run(){
		//While the secretary still has letters to write in their quota
		while(letterQuota > 0){
			try{
				//Type the letter, and send the thread to sleep for the alloted time
				System.out.println("Secretary " + secID + " is typing letter " + letterCount);
				Thread.sleep(speed*1000);
				//Add finished letter to the tray, and update the quota and letter count
				System.out.println("Secretary " + secID + " has finished typing. They have typed " + letterCount + " letter thus far");
				letterTray.Insert(secID);
				letterQuota--;
				letterCount++;
			}
			catch (InterruptedException e) {}
		}
		//When all letters have been typed, print line out and the thread finishes
		System.out.println("Secretary " + secID + " has typed their quota of letters and is leaving");
	}
}

//Manager thread for use as managers
class Manager extends Thread{
	//Storing the letter ascociated with the manager
	private char manID;
	//Storing the manager's stats as well as their quota, and a count for amount of letters signed and a count for
	//how tired they are
	private int markTime, recoveryTime, markQuota, breakCount = 0, markCount = 1;
	//Amount of letters signed before manager needs a break
	private final int breakLimit = 7;
	//Enables access to the tray and lounge
	Tray letterTray;
	Lounge execLounge;
	//Constructor method
	public Manager(char managerID, int manMarkTime, int manRecoveryTime, int manQuota, Tray officeTray, Lounge officeLounge){
		//Passing parameters to the local variables
		manID = managerID;
		markTime = manMarkTime;
		recoveryTime = manRecoveryTime;
		markQuota = manQuota;
		letterTray = officeTray;
		execLounge = officeLounge;
	}
	public void run(){
		//While the manager still has letters to write in their quota
		while (markQuota > 0){
			try{
				//If they have signed enough letters to take a break, go to the exec lounge
				if (breakCount == breakLimit){
					System.out.println("Manager " + manID + " is tired and going to have a break from signing");
					execLounge.TakeBreak(manID);
					Thread.sleep(recoveryTime*1000);
					//After resting in the lounge, reset the count until a break and exit the lounge
					breakCount = 0;
					System.out.println("Manager " + manID + " is ready to get back to work");
					execLounge.BackToWork(manID);
				}
				//Remove letter to the tray, and send the thread to sleep for the alloted time
				letterTray.Remove(manID, markTime);
				System.out.println("Manager " + manID + " is signing letter " + markCount);
				Thread.sleep(markTime*1000);
				//Update quota, and both marked and break tracking counts
				markQuota--;
				markCount++;
				breakCount++;
			}
			catch (InterruptedException e) {}
		}
		//When they have signed all letters for their quota, finish the thread
		System.out.println("Manager " + manID + " has signed all of their quota of letters and is leaving for home");
	}
}

//Buffer for the letter tray
class Tray {
	//Tracks amount of letters in the tray, and whether it is full or empty
	private int letterAmount = 0;
	private boolean full = false;
	private boolean empty = true;
	
	//Method for adding a letter to the tray
	public synchronized void Insert(char secID) {
		//If the tray is full, tell the thread trying to add a letter to wait 
		while (full) {
			try {
				System.out.println("Tray is full. Secretary " + secID + " must wait for a letter to be removed to add a letter");
				wait();
			}
			catch (InterruptedException e) {}
		}
		//If the tray is not full, add a letter to the tray
		letterAmount++;
		System.out.println("Letter has been added by secretary " + secID + ".The tray now contains " + letterAmount + " letters");
		//If there are 5 letters, set full to true
		full = (letterAmount==5);
		//Set empty to false and notify any waiting threads
		empty = false;
		notify();
	}
	// Similarly for remove()
	public synchronized void Remove(char manID, int markTime){
		//If tray is empty, tell thread wanting to remove to wait
		while (empty) {
			try {
				System.out.println("Tray is empty, manager " + manID + " must wait for a letter to be typed to sign one");
				wait();
			}
			catch (InterruptedException e) {}
		}
		//If there are letters in the tray, decrement the letter count
		letterAmount--;
		System.out.println("Letter has been removed by manager " + manID + ".The tray now contains " + letterAmount + " letters");
		//If there are 0 letters in the tray, set empty to true
		empty = (letterAmount==0);
		//Set full to false and notify any waiting threads
		full = false;
		notify();
	}
}

//Buffer for use as executive lounge
class Lounge {
	//Booleans to store full or empty values, no need for count as only 1 allowed in at a time
	private boolean full = false;
	private boolean empty = true;
	
	//Add a thread (manager) to the lounge
	public synchronized void TakeBreak(char manID) {
		//If the lounge is full, tell the thread wanting to access to wait
		while (full) {
			try {
				System.out.println("Lounge is occupied, manager " + manID + " must wait for a break");
				wait();
			}
			catch (InterruptedException e) {}
		}
		//Set full to true and empty to false, notify any waiting threads
		full = true;
		empty = false;
		System.out.println("Manager " + manID + " is currently relaxing in the lounge");
		notify();
	}
	// Remove a thread from the buffer / lounge
	public synchronized void BackToWork(char manID){
		//If the buffer is empty then tell the thread wanting to remove to wait
		while (empty) {
			try {
				System.out.println("There is noone in the lounge to exit");
				wait();
			}
			catch (InterruptedException e) {}
		}
		//Set empty to true and full to false, notify any waiting threads
		empty = true;
		full = false;
		System.out.println("Manager " + manID + " has left the lounge");
		notify();
	}
}
