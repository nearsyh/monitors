public class Voter extends Thread{
	private int id;
    private TallyVotes voteTallier;
    private Printer prt;
    public static PRNG generator;
 	public enum States { 
		Start('S'), Vote('V'), Block('B'), Unblock('U'), Complete('C'), Finished('F');
		private final char value;
		public int getValue() {
			return value;
		}
		States(char value) {
			this.value = value;
		}
	}
	public Voter( int id, TallyVotes voteTallier, Printer prt ) {
        this.id = id;
        this.voteTallier = voteTallier;
        this.prt = prt;
    }

    public void run() {
        prt.print(id, States.Start);
        try {
			sleep(generator.generate(19));
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
        boolean ballot = generator.generate(1) == 1;
        int ticket = voteTallier.vote(id, ballot);
        boolean result = voteTallier.getValue(id, ticket);
        prt.print(id, States.Finished, result);
    }
}