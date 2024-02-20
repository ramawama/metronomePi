import { Button } from "@/components/ui/button"
import { CardTitle, CardHeader, CardContent, CardFooter, Card } from "@/components/ui/card"
import { Label } from "@/components/ui/label"
import { Input } from "@/components/ui/input"

export default function bpmDashboard() {
  return (
    <div className="flex flex-col w-full min-h-screen p-4 md:p-6">
      <main className="flex-1 flex flex-col items-center justify-center gap-4">
        <div className="text-6xl font-bold">120 BPM</div>
        <div className="text-2xl font-bold">Minimum BPM: 120</div>
        <div className="text-2xl font-bold">Maximum BPM: 120</div>
        <div className="flex flex-col gap-4 md:flex-row md:gap-8">
          <Button className="w-full md:w-auto">Refresh BPM</Button>
          <Button className="w-full md:w-auto">Reset Min & Max </Button>
        </div>
        <div className="w-full max-w-md">
          <Card className="mt-20">
            <CardHeader>
              <CardTitle>Set Your BPM</CardTitle>
            </CardHeader>
            <CardContent className="space-y-4">
              <div className="space-y-1">
                <Label htmlFor="bpm">BPM</Label>
                <Input id="bpm" placeholder="Enter your BPM" type="number" />
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
