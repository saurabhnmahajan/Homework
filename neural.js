var s = [
	[1, 1, 1],
	[1, 2, 0],
	[2, -1, -1],
	[2, 0, 0],
	[-1, 2, -1],
	[-2, 1, 1],
	[-1, -1, -1],
	[-2, -2, 0]
];

var t = [
	[-1, -1],
	[-1, -1],
	[-1, 1],
	[-1, 1],
	[1, -1],
	[1, -1],
	[1, 1],
	[1, 1]
];
var w = [[0, 0], [0, 0], [0, 0]];
var w_change = [[0, 0], [0, 0], [0, 0]];

var b = [0, 0];
var  b_change = [0, 0];
var y_in = y = [0, 0];

var epoch = 0, alpha = 0.02;

while(epoch < 100) {
	for(k = 0; k < s.length; k++) {
		alpha = 1.0/((epoch+1)*(k+1));
		var x = s[k];
		for(j = 0; j < 2; j++) {
			y_in[j] = b[j];
			for(i = 0; i < 3; i++) {
				y_in[j] += w[i][j] * x[i];	
			}
		}
		y = y_in;
		for(j = 0; j < 2; j++) {
			for(i = 0; i < 3; i++) {
				w_change[i][j] = 2 * alpha * x[i] * (y[j] - t[k][j]);
				w[i][j] -= w_change[i][j];
				b_change[j] = 2 * alpha * (y[j] - t[k][j]);
				b[j] -= b_change[j];
				w[i][j] = Math.round(w[i][j] * 10000)/10000;
				b[j] = Math.round(b[j] *10000)/10000;
			}
		}

		var error = [0, 0];
		var total = [0, 0];
		for(j = 0; j < 2; j++) {
			for(i = 0; i < 3; i++) {
				total[j] += x[i] * w[i][j];
			}
			error[j] = Math.round(Math.pow((total[j] - t[k][j]), 2)/s.length *10000)/10000;
		}

		w_change = [[0, 0], [0, 0], [0, 0]];
	}
	console.log("Epoch", (epoch+1), "Weight", w);
	console.log("Bias", b, "Error", error);
	if(k > 7) {
		epoch++;
	}
}