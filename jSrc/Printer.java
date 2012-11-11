public class Printer {
    private int voters, left;
    private boolean change[];
    private int param[];
    private synchronized void printState() {
    	for(int i = 0; i < voters; i ++) {
            if(change[i]) {
                System.out.printf("%c", states[i].getValue());
                if(states[i] != Voter.States.Start && states[i] != Voter.States.Complete)
                    System.out.printf(" %d", param[i]);
            }
            System.out.print("\t");
            change[i] = false;
        }
    	System.out.println();
        for(int i = 0; i < voters; i ++)
            assert(!change[i]);
    }
    private Voter.States states[];
    public Printer( int voters ) {
        left = this.voters = voters;
        change = new boolean[voters];
        param = new int[voters];
        states = new Voter.States[voters];
        for(int i = 0; i < voters; i ++)
            System.out.printf("Voter%d\t", i);
        System.out.println();
        for(int i = 0; i < voters; i ++)
            System.out.print("=======\t");
        System.out.println();
    }
    public void Finished( ) {
        change = null;
        param = null;
        states = null;
        for(int i = 0; i < 17; i ++)
        	System.out.print("=");
        System.out.printf("\nAll tours started\n");
    }
	public synchronized void print( int id, Voter.States state ) {
		/* if the state of id has been updated before, then print the stored states */
		if(change[id]) printState();
		assert(!change[id]);
		/* store the new state */
		states[id] = state;
		change[id] = true;
		}
	public synchronized void print( int id, Voter.States state, boolean result ) {
		/* if the state of id has been updated before, then print the stored states */
	    if(change[id]) printState();
	    assert(!change[id]);
	    /* store the new state */
	    states[id] = state;
	    param[id] = result ? 1 : 0;
	    /* if the new state is finished */
	    if(state == Voter.States.Finished) {
	        for(int i = 0; i < voters; i ++)
	            if(i == id) System.out.printf("F %d\t", param[id]);
	            else System.out.print("...\t");
	        System.out.println();
	        if(-- left == 0) Finished();
	    } else change[id] = true;
	}
	public synchronized void print( int id, Voter.States state, int numBlocked ) {
		/* if the state of id has been updated before, then print the stored states */
	    if(change[id]) printState();
	    assert(!change[id]);
	    /* store the new state */
	    states[id] = state;
	    param[id] = numBlocked;
	    change[id] = true;
	}
}
