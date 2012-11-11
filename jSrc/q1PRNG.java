import java.util.Random;

public class q1PRNG {
	private Random rand;
	public q1PRNG() { rand = new Random(1009); }
	public q1PRNG(int seed) { rand = new Random(seed); } // set seed
	public void seed( int seed ) { rand = new Random(seed); } // set seed
	public synchronized int generate() { return Math.abs(rand.nextInt()); } // [0,UINT MAX]
	public synchronized int generate( int u ) { return generate() % (u + 1); } // [0,u]
	public synchronized int generate( int l, int u ) { return generate( u - l ) + l; } // [l,u]
}
