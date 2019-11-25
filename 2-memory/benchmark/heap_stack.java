public class heap_stack{

	public static void main(String[] args) {
		long loopCount = 1024*1024;
	    long t1 = System.currentTimeMillis();
	    for (int i = 0; i < loopCount; i++) {
	        alloc();
	    }
	    long t2 = System.currentTimeMillis();
		for (int i = 0; i < loopCount; i++) {
	        alloc_stack();
	    }
	    long t3 = System.currentTimeMillis();
	    System.out.println("时间消耗：" + (t2 - t1) + "," + (t3-t2) + " 毫秒\n");
	}

	
	private static void alloc() {
		User user = new User();
	}

	private static void alloc_stack() {
		User user;
	}
	static class User {
	}
}

