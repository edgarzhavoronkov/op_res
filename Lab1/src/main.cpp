#include <iostream>
#include <vector>
#include <fstream>
#include <string>


bool phi_is_null(std :: vector<std :: vector<double> >& table) {
	for (int i = 0; i < table[0].size(); ++i) {
		if (table[table.size() - 1][i] != 0){
			return false;
		}
	}
	return true;
}

bool all_constants_are_not_negative(std :: vector<std :: vector<double> >& table) {
	for (int i = 0; i < table.size() - 2; ++i) {
		if (table[i][0] < 0) {
			return false;
		}
	}
	return true;
}

void recalc_table(std :: vector<std :: vector<double> >& table, double solving_element, int solving_row, int solving_column) {
	std :: vector<std :: vector<double> > old_table(table);
	for (int i = 0; i < table[0].size(); ++i) {
		table[solving_row][i] /= solving_element;	
	}
	for (int i = 0; i < table.size(); ++i) {
		if (i == solving_row) {
			table[i][solving_column] = 1;	
		} else {
			table[i][solving_column] = 0;	
		}
	}
	for (int i = 0; i < table.size(); ++i) {
		for (int j = 0; j < table[i].size(); ++j) {
			if (i != solving_row) {
				table[i][j] = old_table[i][j] - old_table[solving_row][j] * old_table[i][solving_column] / solving_element;
			}
		}
	}
}

double get_solving_element(std :: vector<std :: vector<double> >& table, int n, int m, int& s, int& r, std :: string mode) {
	int offset;
	int rows = table.size();
	int columns = table[0].size();

	if (mode == "phi") {
		offset = 1;
	} else if (mode == "zet") {
		offset = 2;
	}

	std::vector<double> theta;
	theta.assign(m, 0);

	double min = 1e9;
	r = 0;

	for (int i = 1; i <= n; ++i){
		if (table[rows - offset][i] < min) {
			min = table[rows - offset][i];
			r = i;
		}
	}

	for (int i = 0; i < m; ++i) {
		theta[i] = table[i][0] / table[i][r];
	}

	min = 1e9;
	s = 0;

	for (int i = 0; i < m; ++i) {
		if (theta[i] > 0 && theta[i] < min) {
			min = theta[i];
			s = i;
		}
	}

	return table[s][r];
}

std :: vector<int>& gen_plan(std :: vector<std :: vector<double> >& table, int rows, int columns, int n, int m){
	if (!all_constants_are_not_negative(table)) {
		for (int i = 0; i < rows - 2; ++i) {
			if (table[i][0] < 0) {
				for (int j = 0; j < columns; ++j) {
					table[rows - 1][j] += table[i][j]; 
				}
			}
		}
		//recalc by phi string
		while (!phi_is_null(table)) {
			int s,r;
			double solving_element = get_solving_element(table, n, m, s,r,"phi");
			recalc_table(table, solving_element, s, r);
		}
		//recalc by target function string
		int s,r;
		double solving_element = get_solving_element(table, n, m, s,r,"zet");
		recalc_table(table, solving_element, s, r);
	} else {
		int s,r;
		double solving_element = get_solving_element(table, n, m, s,r,"zet");
		recalc_table(table, solving_element, s, r);
	}	
}


int main(int argc, char** argv) {
	const char* input_file = argv[1];
    const char* output_file = argv[2];

	std :: ifstream ifs(input_file, std :: ifstream :: in);
    std :: ofstream ofs(output_file, std :: ifstream :: out); 
    
    std :: vector<std :: vector<double> > table;

    int n, m, b_var, s_var;
    ifs >> n >> m >> b_var >> s_var;

    for (int i = 0; i < n; ++i) {
    	std :: vector <double> tmp;
    	for (int j = 0; j < m; ++j) {
    		double val;
    		ifs >> val;
    		tmp.push_back(val);
    	}
    	table.push_back(tmp);
    }

    std :: vector<double> phi;
    phi.assign(m, 0);
    table.push_back(phi);

    gen_plan(table, table.size(), table[0].size(), b_var, s_var);

	for (int i = 0; i < table.size(); ++i) {
    	for (int j = 0; j < table[i].size(); ++j) {
    		ofs << table[i][j] << " ";
    	}
    	ofs << std :: endl;
    }    



	return 0;
}
