import java.util.Date;
import java.util.Vector;

public class TallyVotes {
    private int group_size, ballots;
    Vector<Integer> results = new Vector<Integer>();
    Vector<Integer> waiting = new Vector<Integer>();
    private Printer prt;

    public TallyVotes(int group, Printer prt) {
        group_size = group;
        this.prt = prt;
        ballots = 0;
    }

    public synchronized int vote(int id, boolean ballot) {
    	prt.print(id, Voter.States.Vote, ballot);
    	if(ballots % group_size == 0) {
    		results.add(new Integer(0));
    		waiting.add(new Integer(0));
    	}
    	int index = ballots / group_size;
    	if(ballot) results.set(index, results.elementAt(index) + 1);
    	ballots ++;
    	if(ballots % group_size == 0)
    		notifyAll();
    	return index;
    }
    public synchronized boolean getValue(int id, int ticket) {
    	if(ballots < (ticket+1) * group_size) {
    		waiting.set(ticket, waiting.elementAt(ticket) + 1);
    		prt.print(id, Voter.States.Block, waiting.elementAt(ticket));
    		try { wait();
			} catch (InterruptedException e) { e.printStackTrace(); }
    		prt.print(id, Voter.States.Unblock, waiting.elementAt(ticket) - 1);
    		waiting.set(ticket, waiting.elementAt(ticket) - 1);
    	}
    	prt.print(id, Voter.States.Complete);
    	return results.elementAt(ticket) * 2 > group_size;
    }
    
    public static void main(String[] args) {
    	int totalSize, groupSize, seed;
    	totalSize = args.length >= 1 ? Integer.parseInt(args[0]) : 6;
    	groupSize = args.length >= 2 ? Integer.parseInt(args[1]) : 3;
    	seed = (int) (args.length >= 3 ? Integer.parseInt(args[2]) : (new Date()).getTime()%10000);
    	System.out.printf("%d %d %d\n", totalSize, groupSize, seed);
    	if(totalSize <= 0 || groupSize <= 0 || seed <= 0 || totalSize % groupSize != 0 || groupSize % 2 == 0) {
    		System.out.printf("Usage: Voter.class Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)\n");
    		return;
    	}
    	
    	Printer prt = new Printer(totalSize);
    	TallyVotes tallyVotes = new TallyVotes(groupSize, prt);
    	Voter voters[] = new Voter[totalSize];
    	Voter.generator = new PRNG(seed);
    	for(int i = 0; i < totalSize; i ++) {
    		voters[i] = new Voter(i, tallyVotes, prt);
    		voters[i].start();
    	}
    }
}