import { Button } from "@/components/ui/button"
import { CardTitle, CardHeader, CardContent, CardFooter, Card } from "@/components/ui/card"
import { Label } from "@/components/ui/label"
import { Input } from "@/components/ui/input"

export default function bpmDashboard() {
  return (
    <div className="flex flex-col w-full min-h-screen p-4 md:p-6">
      <header className="flex items-center h-16 px-4 border-b md:px-6">
        <h1 className="text-2xl font-bold">BPM Dashboard</h1>
      </header>
      <main className="flex-1 flex flex-col items-center justify-center gap-8">
        <div className="text-6xl font-bold">120 BPM</div>
        <div className="flex flex-col gap-4 md:flex-row md:gap-8">
          <Button className="w-full md:w-auto">Click to Measure BPM</Button>
          <Button className="w-full md:w-auto">Refresh BPM</Button>
        </div>
        <div className="w-full max-w-md">
          <Card>
            <CardHeader>
              <CardTitle>Set Your BPM</CardTitle>
            </CardHeader>
            <CardContent className="space-y-4">
              <div className="space-y-1">
                <Label htmlFor="bpm">BPM</Label>
                <Input id="bpm" placeholder="Enter your BPM" type="number" />
              </div>
              <div className="space-y-1">
                <Label htmlFor="minBpm">Minimum BPM</Label>
                <Input id="minBpm" placeholder="Enter minimum BPM" type="number" />
              </div>
              <div className="space-y-1">
                <Label htmlFor="maxBpm">Maximum BPM</Label>
                <Input id="maxBpm" placeholder="Enter maximum BPM" type="number" />
              </div>
            </CardContent>
            <CardFooter>
              <Button>Save BPM</Button>
            </CardFooter>
          </Card>
        </div>
      </main>
    </div>
  )
}
