class Printer;

class TallyVotes {
    private int group_size, ballots, countOfTrue;
    private Printer prt;
    private boolean result;

    public TallyVotes(int group, Printer prt) {
        group_size = group;
        prt = prt;
    }

    public synchronized vote(int id, boolean ballot) {
    }
}

class Voter extends Thread {
    private int id;
    private TallyVotes voteTallier;
    private Printer prt;
	public enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Complete = 'C', Finished = 'F' };
	public Voter( int id, TallyVotes voteTallier, Printer prt ) {
        id = id;
        voteTallier = voteTallier;
        prt = prt;
    }

    public void run() {
        prt.print(id, Start);
        yield(generator(19));
        boolean ballot = generator(1) == 1;
        boolean result = voteTallier.vote(id, ballot);
        prt.print(id, Finished, result);
    }
}

class Printer {
    private int voters;
    private boolean *change;
    private int *param;
    private void printState() {
    }
    private Voter::States *states;
    public Printer( int voters ) {
        voters = voters;
        change = new boolean[voters]
        param = new int[voters];
        states = new Voter::States[voters];
        for(unsigned int i = 0; i < voters; i ++)
            cout << "Voter" << i << "\t";
        cout << endl;
        LOOP_PRINT("=======\t", voters);
    }
    public ~Printer( ) {
        delete []change;
        delete []param;
        delete []states;
        LOOP_PRINT("=", 17);
        cout << "All tours started" << endl;
    }
	public synchronized void print( int id, Voter::States state );
	public synchronized void print( int id, Voter::States state, boolean vote );
	public synchronized void print( int id, Voter::States state, int numBlocked );
}
