var i , j ; 
var value = 4503599627370496
for (i = 0 ; i < 3 ; i++) {
  for( j = 0 ; j < 8 ; j++){
		var tile = new Tile({x : j, y : i},value) ; 
		GM.grid.insertTile(tile);
    value /= 2 ; 
  }
}
var last_tile = new Tile({x : 7, y :3 },value*2) ; 
GM.grid.insertTile(last_tile);
    