'use client'

import { Button } from "@/components/ui/button"
import { CardTitle, CardHeader, CardContent, CardFooter, Card } from "@/components/ui/card"
import { Label } from "@/components/ui/label"
import { Input } from "@/components/ui/input" 
import { useEffect, useState } from "react"

export default function bpmDashboard() {
  let [BPM, setBPM] = useState(0);
  let [Max, setMax] = useState(0);
  let [Min, setMin] = useState(0);
  let [BPMinput, setBPMinput] = useState("");


  async function getBPM() {
    await fetch("http://127.0.0.1:5000/bpm/min/")
      .then(response => response.json())
      .then(data => {
        setMin(data['Min']);
      })
      .catch(error => {
        console.error('Error fetching BPM data', error);
      });
    await fetch("http://127.0.0.1:5000/bpm/max/")
      .then(response => response.json())
      .then(data => {
        setMax(data['Max']);
      })
      .catch(error => {
        console.error('Error fetching Max BPM data', error);
      });

    await fetch("http://127.0.0.1:5000/bpm/")
      .then(response => response.json())
      .then(data => {
        setBPM(data['BPM']);
      })
      .catch(error => {
        console.error('Error fetching BPM data', error);
      });
  }

  // Dumb function that looks bad
  useEffect(() => {getBPM()}, []);
  

  // TODO: Add checker in update to ensure numbers are inputted
  async function updateBPM() {
    if(BPMinput != ""){
      await fetch("http://127.0.0.1:5000/bpm/", {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({BPM: Number(BPMinput)})
      }).then(response => {
        if (response.ok) {
          setBPMinput("");
          getBPM();
        } else {
          console.error('Error updating BPM data');
        }
      }).catch(error => {
        console.error('Error updating BPM data', error);
      });
    }
  }

  function deleteMaxMin() {
    fetch("http://127.0.0.1:5000/bpm/max/", {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json'
      },
    }).then(response => {
      if (response.ok) {
        setMax(0)
      } else {
        console.error('Error updating BPM data');
      }
    }).catch(error => {
      console.error('Error updating BPM data', error);
    });

    fetch("http://127.0.0.1:5000/bpm/min/", {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json'
      },
    }).then(response => {
      if (response.ok) {
        setMin(0)
      } else {
        console.error('Error updating BPM data');
      }
    }).catch(error => {
      console.error('Error updating BPM data', error);
    });

  }



  return (
    <div className="flex flex-col w-full min-h-screen p-4 md:p-6">
      <main className="flex-1 flex flex-col items-center justify-center gap-4">
        <div className="text-6xl font-bold">BPM: {BPM} </div>
        <div className="text-2xl font-bold">Minimum BPM: {Min}</div>
        <div className="text-2xl font-bold">Maximum BPM: {Max}</div>
        <div className="flex flex-col gap-4 md:flex-row md:gap-8">
          <Button onClick={getBPM} className="w-full md:w-auto">Refresh BPM</Button>
          <Button onClick={deleteMaxMin} className="w-full md:w-auto">Reset Min & Max </Button>
        </div>
        <div className="w-full max-w-md">
          <Card className="mt-20">
            <CardHeader>
              <CardTitle>Set Your BPM</CardTitle>
            </CardHeader>
            <CardContent className="space-y-4">
              <div className="space-y-1">
                <Label htmlFor="bpm">BPM</Label>
                <Input type="number" id="bpm" value={BPMinput} placeholder="Enter your BPM" onChange={(e) => setBPMinput(e.target.value)} />
              </div>
            </CardContent>
            <CardFooter>
              <Button onClick={updateBPM}>Save BPM</Button>
            </CardFooter>
          </Card>
        </div>
      </main>
    </div>
  )
}
