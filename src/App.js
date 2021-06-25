import humidity from './humidity.svg';
import thermometer from './thermometer.svg';
import './App.css';

import { FirebaseDatabaseNode } from "@react-firebase/database";

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <div className="box">
          <FirebaseDatabaseNode path="nhietdo/">
          {({value}) =>
            <>
              <img src={thermometer} style={{ height: 100, width: 100 }} alt="logo" />
              <p className="value">{value} &deg;C</p>
            </>}
          </FirebaseDatabaseNode>
        </div>
        <div className="box">
        
          <FirebaseDatabaseNode path="doam/">
          {({value}) =>
            <>
            <img src={humidity} style={{ height: 100, width: 100 }} alt="logo" /> 
            <p className="value">{value} %</p>
            </>}
          </FirebaseDatabaseNode>
        </div>
        <div className="box">
          <p>Tấn Tài - Phi Hùng - Huy Đông</p>
        </div>
      </header>
    </div>
  );
}

export default App;
