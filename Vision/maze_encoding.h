

typedef struct {
    int x,y;
}cords;
typedef struct {
    cords width, length;
    int a, b, c, d;
}rect;

class EncodeMaze {
    public:
    cords map_size;
    int maze_x = 9; //cells
    int maze_y= 5;
    cords pt1,pt2 = 0; //rectangular section to check
    double cell_x = 250; //mm
    double cell_y = 250;
    double var_x = 25;
    double var_y = 25;
    //class funcs
    EncodeMaze();
    ~EncodeMaze();
    void getMap(image maze_red);
    
}
EncodeMaze::EncodeMaze(){
    map_size.x = maze_x*cell_x;
    map_size.y = maze_x*cell_y;
}
~EncodeMaze::EncodeMaze(){}

void EncodeMaze::getMap(image maze_red) {
    //gets verticle
    //blank_image = np.zeros((var_y,var_x,3), np.uint8)
    for (int x =1; x < (maze_x-1); x++) {
        a=250*x-var_x;
        b=250*x+var_x;
        
        for (int y=1; y < (maze_y-1); y++) {
            
            c = 250*y-var_y;
            d = 250*y+var_y;
            pt1.x = a; pt1.y = c;
            pt2.x = b; pt2.y = d;
            
            //rect = cv2.rectangle(pt1, pt2, black(0,0,0))
            //rect_maze = rect OR maze_red
            
            //METHOD1
            for (int i =a;i<b;i++){
                for (int j =c;j<d;j++){
                    if (maze_red.item(i,j,2) > 0){
                        //LINE DETECTED
                        
                        break;
                    }
                }
            }
            //METHOD2
            // cv2.bitwise_and(rect, rect_maze)
            b, g, r =maze_red[a:b,c:d,2]
            if (r[:]>0) {
                //LINE DETECTED
            }            
        }
    }
    
}
