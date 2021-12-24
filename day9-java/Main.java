import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.io.IOException;

public class Main {
  public static boolean checkRisk(ArrayList<ArrayList<Integer>> grid, int x, int y, int val) {
    
    try {
      if(grid.get(x).get(y) > val) {
        return true;
      } else {
        return false;
      }
    } catch (Exception e) {
      return true;
    }

  }
  
  public static int checkBasin(ArrayList<ArrayList<Integer>> grid, ArrayList<ArrayList<Boolean>> map, int x, int y) {
    int m = grid.size(), n = grid.get(0).size();

    try {
      if(grid.get(x).get(y) != 9 && !map.get(x).get(y)) {
        map.get(x).set(y, true);

        return 1 + checkBasin(grid, map, x + 1, y) + checkBasin(grid, map, x - 1, y) + checkBasin(grid, map, x, y + 1) + checkBasin(grid, map, x, y - 1);
      } else {
        return 0;
      }
    } catch (Exception e) {
      return 0;
    }

  }

  public static ArrayList<ArrayList<Integer>> readFile(String filename) {
    ArrayList<ArrayList<Integer>> grid = new ArrayList<ArrayList<Integer>>();
    try {
      FileInputStream file = new FileInputStream(filename);
      grid.add(new ArrayList<Integer>());
      int row = 0;

      int i = file.read();
      while(i != -1) {

        if(i == 10) {
          row++;
          grid.add(new ArrayList<Integer>());
        } else {
          grid.get(row).add((char)i - '0');
        }

        i = file.read();
      }

    } catch (IOException e) {
      e.getStackTrace();
      System.out.println("File not found...");
    }

    return grid;
  }

  public static void part_one(String filename) {
    ArrayList<ArrayList<Integer>> grid = readFile(filename);

    int risk = 0;
    for(int x = 0; x < grid.size() - 1; x++) {
      for(int y = 0; y < grid.get(0).size(); y++) {
        int i = grid.get(x).get(y);
        if(checkRisk(grid, x + 1, y, i) && checkRisk(grid, x - 1, y, i) && checkRisk(grid, x, y + 1, i) && checkRisk(grid, x, y - 1, i)) {
          risk += i + 1;
        }
      }
    }

    System.out.println("risk: " + risk);

  }

  public static void part_two(String filename) {
    ArrayList<ArrayList<Integer>> grid = readFile(filename);
    ArrayList<ArrayList<Boolean>> map = new ArrayList<ArrayList<Boolean>>();
    ArrayList<Integer> basins = new ArrayList<Integer>();
    
    for(int x = 0; x < grid.size() - 1; x++) {
      map.add(new ArrayList<Boolean>());

      for(int y = 0; y < grid.get(0).size(); y++) {
        map.get(x).add(false);
      }
    }

    for(int x = 0; x < grid.size() - 1; x++) {
      for(int y = 0; y < grid.get(0).size(); y++) {
        int size = checkBasin(grid, map, x, y);
        
        if(size > 0) basins.add(size);
      }
    }
    Collections.sort(basins);

    int ans = 1;
    for(int i = basins.size() - 1; i > basins.size() - 4; i--) {
      ans *= basins.get(i);
    }

    System.out.println("Answer: " + ans);
  }

  public static void main(String args[]) {
    // part_one("example");
    // part_one("input");
    part_two("example");
    part_two("input");
  }
}
