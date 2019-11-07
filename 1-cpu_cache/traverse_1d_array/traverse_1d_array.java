import java.util.Date;


public class traverse_1d_array{
    public static void main(String args[]){
		int ch;
		int TESTN = 4096;
		boolean slowMode = false;
        for (String arg : args) {
            if ("-f".equals(arg)) {
                slowMode = false;
                break;
            } else if ("-s".equals(arg)) {
                slowMode = true;
                break;
            }
        }

		char [][]arr = new char[TESTN][TESTN];
		Date start = new Date();
		if (!slowMode) {
			for(int i = 0; i < TESTN; i++) {
				for(int j = 0; j < TESTN; j++) {
					//arr[i][j]是连续访问的
					arr[i][j] = 0;
				}
			}
		} else {
			for(int i = 0; i < TESTN; i++) {
				for(int j = 0; j < TESTN; j++) {
					//arr[j][i]是不连续访问的
					arr[j][i] = 0;
				}
			}
		}

		System.out.println(new Date().getTime()-start.getTime());
    }
}

