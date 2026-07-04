/**
 * GridPath-Optimizer-3D
 * 
 * 3D DFS-based solver for energy-constrained grid traversal.
 * Dimensions: depth (layer) × rows × cols
 * 
 * Movement: up/down/left/right + layer switching (6 directions)
 * 
 * Constraints:
 * - Same layer: climb 1.5m max (costs energy), jump 2.5m max (free)
 * - Cross layer: climb 3.0m max (costs energy), jump 10.0m max (free)
 * 
 * Output:
 * - 1 + minimum energy if path exists
 * - 0 if no path exists
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class GridPathSolver3D {
private:
    int depth, rows, cols;
    vector<vector<vector<int>>> height;      // [depth][row][col]
    vector<vector<vector<bool>>> visited;    // [depth][row][col]
    vector<vector<vector<int>>> minEnergy;   // [depth][row][col] for pruning
    int minFinalEnergy;
    
    // 6 directions: (depth, row, col) offsets
    const int dd[6] = {-1, 0, 0, 0, 0, 1};
    const int dr[6] = {0, -1, 0, 1, 0, 0};
    const int dc[6] = {0, 0, 1, 0, -1, 0};
    
    // Constraints (heights are integers, multiplied by 10 internally)
    const double MAX_CLIMB_SAME_LAYER = 1.5;
    const double MAX_JUMP_SAME_LAYER = 2.5;
    const double MAX_CLIMB_CROSS_LAYER = 3.0;
    const double MAX_JUMP_CROSS_LAYER = 10.0;
    
    int totalStatesExplored;
    int pruningHits;
    
    bool isValid(int d, int r, int c) const {
        return d >= 0 && d < depth &&
               r >= 0 && r < rows &&
               c >= 0 && c < cols;
    }
    
    /**
     * Calculate energy cost and check passability.
     * @param d,r,c      Current position
     * @param nd,nr,nc   Target position
     * @param isCrossLayer  Whether moving between layers
     * @return Energy cost (>=0) if passable, -1 if impassable
     */
    int calcEnergy(int d, int r, int c, int nd, int nr, int nc, bool isCrossLayer) const {
        int fromH = height[d][r][c];
        int toH = height[nd][nr][nc];
        int diff = toH - fromH;
        
        double maxClimb, maxJump;
        if (isCrossLayer) {
            maxClimb = MAX_CLIMB_CROSS_LAYER;
            maxJump = MAX_JUMP_CROSS_LAYER;
        } else {
            maxClimb = MAX_CLIMB_SAME_LAYER;
            maxJump = MAX_JUMP_SAME_LAYER;
        }
        
        if (diff > 0) {
            // Climbing up
            if (diff > maxClimb * 10) return -1;
            return diff;  // 1 meter = 1 energy
        } else {
            // Jumping down
            if (-diff > maxJump * 10) return -1;
            return 0;  // Jump down is free
        }
    }
    
    /**
     * Depth-First Search with pruning
     */
    void dfs(int d, int r, int c, int currentEnergy) {
        totalStatesExplored++;
        
        // Pruning: if we already reached this cell with less energy
        if (currentEnergy >= minEnergy[d][r][c]) {
            pruningHits++;
            return;
        }
        minEnergy[d][r][c] = currentEnergy;
        
        // Reached right side (any layer)
        if (c == cols - 1) {
            minFinalEnergy = min(minFinalEnergy, currentEnergy);
            return;
        }
        
        visited[d][r][c] = true;
        
        // Explore 6 directions
        for (int i = 0; i < 6; i++) {
            int nd = d + dd[i];
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (!isValid(nd, nr, nc)) continue;
            if (visited[nd][nr][nc]) continue;
            
            bool isCrossLayer = (nd != d);
            int energyCost = calcEnergy(d, r, c, nd, nr, nc, isCrossLayer);
            if (energyCost == -1) continue;
            
            dfs(nd, nr, nc, currentEnergy + energyCost);
        }
        
        visited[d][r][c] = false;
    }
    
public:
    GridPathSolver3D(int d, int r, int c) 
        : depth(d), rows(r), cols(c), minFinalEnergy(INT_MAX),
          totalStatesExplored(0), pruningHits(0) {
        height.assign(depth, vector<vector<int>>(rows, vector<int>(cols, 0)));
        visited.assign(depth, vector<vector<bool>>(rows, vector<bool>(cols, false)));
        minEnergy.assign(depth, vector<vector<int>>(rows, vector<int>(cols, INT_MAX)));
    }
    
    void setHeight(int d, int r, int c, int h) {
        height[d][r][c] = h;
    }
    
    /**
     * Solve: start from any layer, any row, column 0
     */
    bool solve() {
        minFinalEnergy = INT_MAX;
        totalStatesExplored = 0;
        pruningHits = 0;
        
        // Reset state
        for (int d = 0; d < depth; d++) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    visited[d][r][c] = false;
                    minEnergy[d][r][c] = INT_MAX;
                }
            }
        }
        
        // Start from any layer, any row, leftmost column
        for (int d = 0; d < depth; d++) {
            for (int r = 0; r < rows; r++) {
                dfs(d, r, 0, 0);
            }
        }
        return minFinalEnergy != INT_MAX;
    }
    
    int getMinEnergy() const { return minFinalEnergy; }
    int getStatesExplored() const { return totalStatesExplored; }
    int getPruningHits() const { return pruningHits; }
    double getPruningEfficiency() const {
        return totalStatesExplored > 0 ? 
            (double)pruningHits / totalStatesExplored * 100 : 0;
    }
    
    void printGrid() const {
        for (int d = 0; d < depth; d++) {
            cout << "=== Layer " << d << " (" << rows << "x" << cols << ") ===\n";
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    cout << setw(3) << height[d][r][c] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    
    void printResult(bool verbose = false) {
        bool exists = solve();
        
        if (verbose) {
            cout << "=== Statistics ===\n";
            cout << "Path exists: " << (exists ? "Yes" : "No") << endl;
            if (exists) {
                cout << "Minimum energy: " << minFinalEnergy << endl;
            }
            cout << "States explored: " << totalStatesExplored << endl;
            cout << "Pruning hits: " << pruningHits << endl;
            cout << "Pruning efficiency: " << fixed << setprecision(2) 
                 << getPruningEfficiency() << "%\n\n";
        }
        
        cout << (exists ? "1" : "0") << endl;
        if (exists) {
            cout << minFinalEnergy << endl;
        }
    }
};

// ==================== Main ====================

int main(int argc, char* argv[]) {
    string filename;
    bool verbose = false;
    
    // Parse arguments
    if (argc > 1) {
        filename = argv[1];
        for (int i = 2; i < argc; i++) {
            if (string(argv[i]) == "-v" || string(argv[i]) == "--verbose") {
                verbose = true;
            }
        }
    } else {
        cout << "Enter input file path: ";
        cin >> filename;
    }
    
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: Cannot open file '" << filename << "'" << endl;
        cout << 0 << endl;
        return 0;
    }
    
    int depth, rows, cols;
    fin >> depth >> rows >> cols;
    
    if (depth <= 0 || rows <= 0 || cols <= 0) {
        cerr << "Error: Invalid dimensions" << endl;
        cout << 0 << endl;
        return 0;
    }
    
    GridPathSolver3D solver(depth, rows, cols);
    
    for (int d = 0; d < depth; d++) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int h;
                if (!(fin >> h)) {
                    cerr << "Error: Insufficient data at layer " << d 
                         << ", row " << r << ", col " << c << endl;
                    cout << 0 << endl;
                    return 0;
                }
                solver.setHeight(d, r, c, h);
            }
        }
    }
    
    fin.close();
    
    solver.printGrid();
    solver.printResult(verbose);
    
    return 0;
}
