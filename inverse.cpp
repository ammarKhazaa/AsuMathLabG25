CMatrix CMatrix::inverse(CMatrix &m){
	CMatrix x;
	CMatrix	w(m.nC, m.nC, MI_EYE, 0.0000);// makes an eye matrix
	if (m.nC != m.nR)throw("invalid invesion");
	else {
		x = m;
		double a;
		double hit;
		int cou = 1;
		for (int i = 0; i<x.nR; i++)
		{
			a = x.values[i][i];

			if (a == 0)throw("invalid inversion");
			else{
				for (int j = 0; j<x.nC; j++)
				{
					x.values[i][j] = x.values[i][j] / a;
					w.values[i][j] = w.values[i][j] / a;
				}

				for (int z = 0; z<x.nR; z++)
				{
					if (z != i){
						hit = x.values[z][i];

						for (int c = 0; c < x.nC; c++)
						{

							x.values[z][c] = x.values[z][c] - hit*x.values[i][c];
							w.values[z][c] = w.values[z][c] - hit*w.values[i][c];

						}

					}
				}
			}

		}

	}
	cout << "right= \n\n" << x << "\n\n";
	cout << "inverse= \n\n" << w << "\n\n";
	return w;

}