string result;
	stringstream ss(s);
	stack<int> st;
	stack<char> op;
	string token;
	while (ss >> token) {
		if (token == "+" || token == "-" || token == "*" || token == "/" || token == "(" || token == ")") {
			op.push(token[0]);
		}
		else {
			st.push(stoi(token));
		}
	}