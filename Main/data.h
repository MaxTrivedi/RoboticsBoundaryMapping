//We need to know the maximum number of data items and rows of results we need before starting
#define MAX_RESULTS 100
#define NUM_ITEMS 3

class Data_c {

  public:

    float results[MAX_RESULTS][NUM_ITEMS];
    int results_index = 0;
    
    Data_c() {

    }


    bool resultsFull() {
        return results_index >= MAX_RESULTS;
    }
    
    void updateResults(float new_items[NUM_ITEMS]) {
        for( int i = 0; i < NUM_ITEMS; i++ ) {
          results[ results_index ][i] = new_items[i];
        }
        results_index++;
    }
    
    void reportResultsOverSerial() {
      
      if( SERIAL_ACTIVE ) Serial.print( "Time(ms): " );
      if( SERIAL_ACTIVE ) Serial.println( millis() );
      delay(1);
      
      int row = 0;
      int col = 0;  
      
      for( row = 0; row < MAX_RESULTS; row++ ) {
        if( SERIAL_ACTIVE ) Serial.print( row );
        delay(1);
        if( SERIAL_ACTIVE ) Serial.print( "," );
        delay(1);
        // print x y theta
        for( col = 0; col < 3; col++ ) {
          if( SERIAL_ACTIVE ) Serial.print( results[row][col], 2 );
          delay(1);
          if( SERIAL_ACTIVE ) Serial.print( "," );
          delay(1);
        }
    
        // Printed "x,y,theta", now needs a new line.
        if( SERIAL_ACTIVE ) Serial.print( "\n" ); // new row
      }
    
      if( SERIAL_ACTIVE ) Serial.println( "---End of Results ---\n\n" );
    }
};
