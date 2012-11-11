public class q1Voter extends Thread{
	private int id;
    private q1TallyVotes voteTallier;
    private q1Printer prt;
    public static q1PRNG generator;
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
	public q1Voter( int id, q1TallyVotes voteTallier, q1Printer prt ) {
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