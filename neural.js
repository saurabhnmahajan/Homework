var s = [[1, 1], [1, -1], [-1, 1], [-1, -1]];
var t = [-1, 1, 1, -1];

// variables used without a number represent data between input and hidden layer
// while the ones with number(eg: w1, b1) represent data b/w hidden and output layer.
var w = [[setrandom(), setrandom()], [setrandom(), setrandom()]];
var w1 = [setrandom(), setrandom()];
var b = [setrandom(), setrandom()];
var b1 = setrandom();
var delta = [0, 0], delta1 = 0 , z_in = [0, 0], z = [0, 0];
var epoch = 0, alpha = 1;

function f(x) {
	return Math.tanh(x/2);
}

function f1(x) {
	return (1 - Math.pow(f(x), 2))/2;
}

function roundOff(x) {
	return Math.round(x * 1000) / 1000;
}

function setrandom() {
	var n = roundOff(Math.random() - 0.5);
	if(n < 0)
		return (n -= 0.1);
	else
		return n;
}
console.log("Initial Weights and bias from input to hidden layer", w, b);
console.log("Initial Weights and bias from hidden to output layer", w1, b1);
while(epoch < 1000) {
	console.log("Epoch", (epoch+1));
	for(k = 0; k < 4; k++) {
		w_change = [[0, 0],[0, 0]];
		w1_change =[0, 0];
		b_change = [0, 0];
		b1_change = 0;
		for(j = 0; j < 2; j++) {
			z_in[j] = b[j];
			for(i = 0; i < 2; i++) {
				z_in[j] += w[i][j] * s[k][i];
			}
			z[j] = f(z_in[j]);
		}
		y_in = b1;
		for(j = 0; j < 2; j++) {
			y_in += w1[j] * z[j];
		}
		y = f(y_in);
		
		//error backpropagation
		delta1 = (t[k] - y) * f1(y_in);
		delta[0] = (delta1 * w1[0] + delta1 * w1[1]) * f1(z_in[0]);
		delta[1] = (delta1 * w1[0] + delta1 * w1[1]) * f1(z_in[1]);
		for(j = 0; j < 2; j++) {
			for(i = 0; i < 2; i++) {
				w_change[i][j] = alpha * delta[j] * s[k][i];
			}
			b_change[j] = alpha * delta[j];
		}
		w1_change = [alpha * delta1 * z[0], alpha * delta1 * z[1]];
		b1_change = alpha * delta1;
		
		//update the weights and biases
		for(j = 0; j < 2; j++) {
			for(i = 0; i < 2; i++) {
				w[i][j] += w_change[i][j];
				w[i][j] = roundOff(w[i][j]);
			}
			b[j] += b_change[j];
			b[j] = roundOff(b[j]);
		}
		for(j = 0; j < 2; j++) {
			w1[j] += w1_change[j];
			w1[j] = roundOff(w1[j]);
		}
		b1 += b1_change;
		b1 = roundOff(b1);
		console.log("Input and targets are:", s[k][0], s[k][1], t[k])
		console.log("Weights and bias from input to hidden layer", w, b);
		console.log("Weights and bias from hidden to output layer", w1, b1);
	}
	if(k >= 4) {
		epoch++;
	}
}