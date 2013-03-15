// cut rod problem:
//   dynamic planning algorithm in JavaScript. 
var max = Math.max;

//array index start from 1.
var p = [ /*unused*/, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 ];

function cutRod(p, n) {
  if (n == 0)
    return 0;
  var q = -Infinity;
  for (var i = 1; i <= n; i++)
    q = max(q, p[i] + cutRod(p, n - i));
  return q;
}

function memoizedCutRod(p, n) {
  var r = new Array(1 + n); //include index 0
  for (var i = 0; i <= n; i++)
    r[i] = -Infinity;
  return memoizedCutRodAux(p, n, r);
}

function memoizedCutRodAux(p, n, r) {
  if (r[n] >= 0)
    return r[n];
  var q;
  if (n == 0)
    q = 0;
  else {
    q = -Infinity;
    for (var i = 1; i <= n; i++)
      q = max(q, p[i] + memoizedCutRodAux(p, n - i, r));
  }
  r[n] = q;
  return q;
}

function bottomUpCutRod(p, n) {
  var r = new Array(1 + n);
  r[0] = 0;
  var q;
  for (var j = 1; j <= n; j++) {
    q = -Infinity;
    for (var i = 1; i <= j; i++)
      q = max(q, p[i] + r[j - i]);
    r[j] = q;
  }
  return r[n];
}

function extendedBottomUpCutRod(p, n) {
  var r = new Array(1 + n); // r[0..n]
  var s = new Array(1 + n); // s[0..n]
  r[0] = 0;
  s[0] = 0; //XXX left out in CLRS
  var q;
  for (var j = 1; j <= n; j++) { //sub-problem size=j
    q = -Infinity;
    for (var i = 1; i <= j; i++) //find optimal result
      if (q < p[i] + r[j - i]) {
        q = p[i] + r[j - i];
  s[j] = i; //best choice for 1st cut when sub-problem size=j
      }
    r[j] = q; //save best result
  }
  return {"r": r, "s": s}; // tuple as a object of 2 array
}

function printCutRodSolution(p, n) {
  var rs, r, s;
  rs = extendedBottomUpCutRod(p, n);
  s = rs.s;
  r = rs.r;
  console.log("\nn: "+n);
  console.log("Total price: "+r[n]);
  var ln = "Solution: ";
  var dl = " -> ";
  while (n > 0) {
    ln += s[n] + dl;
    n = n - s[n];
  }
  console.log(ln.slice(0, -dl.length));
}

var len = p.length - 1;
console.log("len="+len);

console.time('take1');
var r1 = cutRod(p, 10);
console.timeEnd('take1');

console.time('take2');
var r2 = memoizedCutRod(p, 10);
console.timeEnd('take2');

console.time('take3');
var r3 = bottomUpCutRod(p, 10);
console.timeEnd('take3');

console.time('take4');
var r4, s4, tp;
tp = extendedBottomUpCutRod(p, 10);
console.log("p: "+p+"\n");
var t = {"tuple" : tp};
console.debug(t);
console.timeEnd('take4');

for (var i=10; i > 0; i--)
  printCutRodSolution(p, i);

alert(
"r1="+r1+","+
"r2="+r2+","+
"r3="+r3+","+
"r4="+tp.r[10]);
